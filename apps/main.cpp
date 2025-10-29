#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <cpr/cpr.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <implot.h>
#include <jni.h>
import std;
import sdl_load_wrapper;
import texture;
import gl_config;
import widgets;
import nlohmann.json;
using json = nlohmann::json;
import bt;
import scroll;

SDL_Window *window{};
SDL_WindowFlags window_flags{};
SDL_GLContext gl_context{};
ImGuiIO ioObject{};
ImGuiIO &io = ioObject;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
SDL_AppResult app_quit = SDL_APP_CONTINUE;
// audio
SDL_AudioDeviceID audioDevice{};
MIX_Mixer *mixer{};
MIX_Track *track{};
MIX_Audio *audio{};
// font
ImFont *font{};
// image
std::vector<texture::image_data> gif_data{};
//ssl
cpr::SslOptions ssl_options {};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO);
    const char *glsl_version = gl_config::init();
    // Window
    window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 625, 1000, window_flags);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    SDL_GL_SetSwapInterval(1); // VSYNC
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);
    IMGUI_CHECKVERSION();
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImPlot::CreateContext();
    io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    SDL_Surface *surface;
    texture::image_data image{};
    IMG_Animation *anim = IMG_LoadAnimation("nameless_deity.gif");
    gif_data.reserve(anim->count);
    for (int i = 0; i < anim->count; i++)
    {
        surface = anim->frames[i];
        surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        texture_from_surface(surface, image);
        gif_data.push_back(image);
    }
    SDL_DestroySurface(surface);
    //Audio
    audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    MIX_Init();
    mixer = MIX_CreateMixerDevice(audioDevice, nullptr);
    track = MIX_CreateTrack(mixer);
    //Fonts
    size_t datasize{};
    void *data2{SDL_LoadFileWrapper("Ubuntu-Regular.ttf", &datasize)};
    font = io.Fonts->AddFontFromMemoryTTF(data2, datasize, 30);
    //CA certs
    void *data {SDL_LoadFileWrapper("cacert-2025-09-09.pem", &datasize)};
    ssl_options = cpr::Ssl(cpr::ssl::CaBuffer(std::move(std::string(static_cast<char*>(data), datasize))));
    //Bluetooth
    JNIEnv* env = (JNIEnv*)SDL_GetAndroidJNIEnv();
    jobject activity = (jobject)SDL_GetAndroidActivity();
    bt::init(env, activity);
    env->DeleteLocalRef(activity);
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // Poll and handle events (inputs, window resize, etc.)
    ImGui_ImplSDL3_ProcessEvent(event);
    if (event->type == SDL_EVENT_QUIT)
    {
        app_quit = SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
        event->window.windowID == SDL_GetWindowID(window)) // Use the event parameter
    {
        app_quit = SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppIterate(void *appstate)
{
    if (app_quit != SDL_APP_CONTINUE)
        return app_quit;

    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
    {
        SDL_Delay(10);
        return SDL_APP_CONTINUE;
    }
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    ImVec2 window_size = ImGui::GetWindowSize();
    static float time = 0.0f;
    time += ImGui::GetIO().DeltaTime;

    ImGui::PushFont(font);

    ImGui::BeginTable("ImageTable", 3, ImGuiTableFlags_SizingStretchProp);
    ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthStretch, 0.1f);
    ImGui::TableSetupColumn("Center", ImGuiTableColumnFlags_WidthStretch, 0.80f);
    ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthStretch, 0.1f);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    static constexpr std::string_view title = "Cross Compile Fun!";
    widgets::centered_text(title);
    static std::string fps_text{};
    fps_text = std::format("FPS: {:.1f}", ImGui::GetIO().Framerate);
    widgets::centered_text(fps_text);
    ImGui::NewLine();
    widgets::animated_waves(time, window_size);
    ImGui::NewLine();
    widgets::gif(time, window_size, gif_data);
    ImGui::NewLine();
    widgets::centered_text("Web Requests!");
    ImGui::NewLine();
    static cpr::AsyncResponse future;
    static bool requestPending = false;
    static float lastRequestTime1 = 0.0f;
    static cpr::Response r {};
    static json response {};
    if (!requestPending && time - lastRequestTime1 >= 5.0f)
    {
        future = cpr::GetAsync(cpr::Url{"https://uselessfacts.jsph.pl/random.json?language=en"}, ssl_options);
        requestPending = true;
        lastRequestTime1 = time;
    }

    if (requestPending && future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        r = future.get();
        response = json::parse(r.text);
        requestPending = false;
    }
    if (r.text.empty())
    {
        widgets::centered_text("Waiting for response...");
    }
    else
    {
        ImGui::TextWrapped(response["text"].get<std::string>().c_str());
    }
    ImGui::NewLine();
    widgets::centered_text("Bluetooth!");
    ImGui::NewLine();
    static json bt_devices {};
    static float lastRequestTime2 = 0.0f;
    static std::vector<std::string> bt_device_names;
    if (time - lastRequestTime2 >= 5.0f)
    {
        bt_devices = bt::get_paired_devices();
        bt_device_names.clear();
        for (const auto& device : bt_devices)
        {
            bt_device_names.push_back(device["name"]);
        }
        lastRequestTime2 = time;
    }
    static int selected_device = -1;
    if(bt_device_names.size() > 0)
    {
        widgets::centered_listbox("###Bluetooth Devices", &selected_device, bt_device_names);
    }
    else
    {
        widgets::centered_text("Searching for devices...");
    }
    if (selected_device >= 0 && selected_device < bt_devices.size())
    {
        ImGui::NewLine();
        widgets::centered_text("Selected Device: " + bt_device_names[selected_device]);
        ImGui::NewLine();
        widgets::centered_text("Selected MAC Address: " + std::string(bt_devices[selected_device]["address"]));
    }
    ImGui::NewLine();
    widgets::centered_text("Connection Status: " + std::string(bt::is_connected() ? "ON" : "OFF"));
    ImGui::NewLine();
    static bool connected = false;
    if (ImGui::Button(connected ? "Disconnect" : "Connect", ImVec2(window_size.x * 0.8f, 0)))
    {
        if (!connected)
        {
            std::string address = bt_devices[selected_device]["address"];
            connected = bt::connect(address);
        }
        else
        {
            bt::disconnect();
            connected = false;
        }
    }
    ImGui::NewLine();
    widgets::centered_text("Serial Port Buffer");
    static float lastRequestTime3 {};
    static std::string buffer {};
    static json mcu_output {};
    if (time - lastRequestTime3 >= 5.0f)
    {
        buffer = bt::buffer();
        if(buffer.size() > 0)
        {
            mcu_output = json::parse(buffer);
        }
        lastRequestTime3 = time;
    }
    ImGui::TextWrapped(mcu_output.dump(4).c_str());
    ImGui::NewLine();
    if (ImGui::Button("Twisted Garden", ImVec2(window_size.x * 0.4f, 0)))
    {
        audio = MIX_LoadAudio(mixer, "twisted_garden.mp3", true);
        MIX_SetTrackAudio(track, audio);
        MIX_PlayTrack(track, 0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Sky After Rain", ImVec2(window_size.x * 0.4f, 0)))
    {
        audio = MIX_LoadAudio(mixer, "sky_after_rain.mp3", true);
        MIX_SetTrackAudio(track, audio);
        MIX_PlayTrack(track, 0);
    }

    ImGui::SameLine();
    ImGui::NewLine();
    static bool music_playing{true};
    if (ImGui::Button(music_playing ? "Pause" : "Resume", ImVec2(window_size.x * 0.8f, 0)))
    {
        if (music_playing)
        {
            MIX_PauseTrack(track);
        }
        else
        {
            MIX_ResumeTrack(track);
        }
        music_playing = !music_playing;
    }
    ImGui::PopFont();
    ImGui::EndTable();
    ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
    scroll::anywhere(delta, ImGuiMouseButton_Left);
    ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
    ImGui::End();
    ImGui::Render();

    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
    return SDL_APP_CONTINUE;
}
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    SDL_GL_DestroyContext(gl_context);

    SDL_CloseAudioDevice(audioDevice);
    MIX_DestroyMixer(mixer);
    MIX_DestroyAudio(audio);
    MIX_Quit();

    SDL_DestroyWindow(window);
    SDL_Quit();
}
