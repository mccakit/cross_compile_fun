#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <implot.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
import std;
import sdl_load_wrapper;
struct ImageData
{
    int width = 0;
    int height = 0;
    GLuint texture = 0;
};

// Simple helper function to load an image into a OpenGL texture with common settings
void texture_from_surface(SDL_Surface *surface, ImageData &image)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,
                 0,       // mipmap level
                 GL_RGBA, // internal format
                 surface->w, surface->h,
                 0,                // border
                 GL_RGBA,          // format of pixel data
                 GL_UNSIGNED_BYTE, // type of pixel data
                 surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    image.texture = texture;
    image.height = surface->h;
    image.width = surface->w;
}

struct app_state
{
    SDL_Window *window;
    SDL_WindowFlags window_flags;
    SDL_GLContext gl_context;
    ImGuiIO ioObject;
    ImGuiIO &io = ioObject;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_AppResult app_quit = SDL_APP_CONTINUE;
    // audio
    SDL_AudioDeviceID audioDevice{};
    MIX_Mixer *mixer{};
    MIX_Track *track{};
    MIX_Audio *audio{};
    // font
    ImFont *proggy_clean_36;
    //image
    std::vector<ImageData> gif_data;
};
app_state state{};
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO);

#ifdef IMGUI_IMPL_OPENGL_ES3
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char *glsl_version = "#version 300 es";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif __APPLE__
    // GL 3.2 Core + GLSL 150
    const char *glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // OpenGL Core 4.6
    const char *glsl_version = "#version 460";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
#endif
    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Set window flags
    state.window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    state.window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 625, 1000, state.window_flags);
    state.gl_context = SDL_GL_CreateContext(state.window);
    SDL_GL_MakeCurrent(state.window, state.gl_context);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_SetWindowPosition(state.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(state.window);
    IMGUI_CHECKVERSION();
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImPlot::CreateContext();
    state.io = ImGui::GetIO();
    state.io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    state.io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(state.window, state.gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    SDL_Surface *surface;
    ImageData image{};
    IMG_Animation* anim = IMG_LoadAnimation("nameless_deity.gif");
    state.gif_data.reserve(anim->count);
    for (int i = 0; i < anim->count; i++) {
        surface = anim->frames[i];
        surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        texture_from_surface(surface, image);
        state.gif_data.push_back(image);
    }
    SDL_DestroySurface(surface);
    state.audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    MIX_Init();
    state.mixer = MIX_CreateMixerDevice(state.audioDevice, nullptr);
    state.track = MIX_CreateTrack(state.mixer);

    size_t datasize1{};
    void *data1{SDL_LoadFileWrapper("Roboto_Condensed-Regular.ttf", &datasize1)};
    state.io.Fonts->AddFontFromMemoryTTF(data1, datasize1, 18);

    size_t datasize2{};
    void *data2{SDL_LoadFileWrapper("Roboto_Condensed-Regular.ttf", &datasize2)};
    state.proggy_clean_36 = state.io.Fonts->AddFontFromMemoryTTF(data2, datasize2, 36);
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // Poll and handle events (inputs, window resize, etc.)
    ImGui_ImplSDL3_ProcessEvent(event);
    if (event->type == SDL_EVENT_QUIT)
    {
        state.app_quit = SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
        event->window.windowID == SDL_GetWindowID(state.window)) // Use the event parameter
    {
        state.app_quit = SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppIterate(void *appstate)
{
    if (state.app_quit != SDL_APP_CONTINUE)
        return state.app_quit;

    if (SDL_GetWindowFlags(state.window) & SDL_WINDOW_MINIMIZED)
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

    ImVec2 windowSize = ImGui::GetWindowSize();
    static float time = 0.0f;
    time += ImGui::GetIO().DeltaTime;

    ImGui::BeginTable("ImageTable", 3, ImGuiTableFlags_SizingStretchProp);
    ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthStretch, 0.1f);
    ImGui::TableSetupColumn("Center", ImGuiTableColumnFlags_WidthStretch, 0.80f);
    ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthStretch, 0.1f);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    ImGui::PushFont(state.proggy_clean_36);

    static constexpr std::string_view text1 = "Cross Compile Fun!";
    float text1_width = ImGui::CalcTextSize(text1.data()).x;
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - text1_width) * 0.5f);
    ImGui::Text("%s", text1.data());

    static std::array<char, 32> fps_text;
    std::snprintf(fps_text.data(), fps_text.size(), "FPS: %.1f", ImGui::GetIO().Framerate);
    float fps_width = ImGui::CalcTextSize(fps_text.data()).x;
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - fps_width) * 0.5f);
    ImGui::Text("%s", fps_text.data());

    ImGui::PopFont();

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    if (ImPlot::BeginPlot("Animated Waves", ImVec2(windowSize.x * 0.8f, 0), ImPlotFlags_NoFrame | ImPlotFlags_NoInputs))
    {
        static std::array<float, 100> x_data;
        static std::array<float, 100> y_sine;
        static std::array<float, 100> y_cosine;
        for (int i = 0; i < 100; ++i)
        {
            float x = i * 0.1f;
            x_data[i] = x;
            y_sine[i] = std::sin(x + time);   // Phase shift by time
            y_cosine[i] = std::cos(x + time); // Phase shift by time
        }
        ImPlot::SetupAxesLimits(x_data.front(), x_data.back(), -1.05, 1.05, ImPlotCond_Always);
        ImPlot::PlotLine("Sine", x_data.data(), y_sine.data(), 100);
        ImPlot::PlotLine("Cosine", x_data.data(), y_cosine.data(), 100);
        ImPlot::EndPlot();
    }

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    int frame = static_cast<int>(time / (1.0F / 50.0f)) % state.gif_data.size();
    float aspect_ratio = static_cast<float>(state.gif_data[0].width) / static_cast<float>(state.gif_data[0].height);
    ImVec2 image_size = ImVec2(windowSize.x * 0.8f, windowSize.x * 0.8f / aspect_ratio);
    ImGui::Image((ImTextureID)(intptr_t)state.gif_data[frame].texture, image_size);

    ImGui::PushFont(state.proggy_clean_36);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    if (ImGui::Button("Twisted Garden", ImVec2(windowSize.x * 0.4f, 0)))
    {
        state.audio = MIX_LoadAudio(state.mixer, "twisted_garden.mp3", true);
        MIX_SetTrackAudio(state.track, state.audio);
        MIX_PlayTrack(state.track, 0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Sky After Rain", ImVec2(windowSize.x * 0.4f, 0)))
    {
        state.audio = MIX_LoadAudio(state.mixer, "sky_after_rain.mp3", true);
        MIX_SetTrackAudio(state.track, state.audio);
        MIX_PlayTrack(state.track, 0);
    }

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(1);
    static bool music_playing{true};
    if (ImGui::Button(music_playing ? "Pause" : "Resume", ImVec2(windowSize.x * 0.8f, 0)))
    {
        if (music_playing)
        {
            MIX_PauseTrack(state.track);
        }
        else
        {
            MIX_ResumeTrack(state.track);
        }
        music_playing = !music_playing;
    }

    ImGui::PopFont();
    ImGui::EndTable();
    ImGui::End();
    ImGui::Render();

    glViewport(0, 0, (int)state.io.DisplaySize.x, (int)state.io.DisplaySize.y);
    glClearColor(state.clear_color.x * state.clear_color.w, state.clear_color.y * state.clear_color.w,
                 state.clear_color.z * state.clear_color.w, state.clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(state.window);
    return SDL_APP_CONTINUE;
}
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    ImGui::DestroyContext();
    ImPlot::DestroyContext();
    SDL_GL_DestroyContext(state.gl_context);

    SDL_CloseAudioDevice(state.audioDevice);
    MIX_DestroyMixer(state.mixer);
    MIX_DestroyAudio(state.audio);
    MIX_Quit();

    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
