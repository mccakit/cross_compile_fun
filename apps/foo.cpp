#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

/* Constants */
constexpr int kScreenWidth{ 1280 };
constexpr int kScreenHeight{ 720 };

/* Global Variables */
SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };

/* Function Prototypes */
bool init();
void close();
void render();

/* Function Implementations */
bool init()
{
    bool success{ true };

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("ImGui Hello World", kScreenWidth, kScreenHeight, SDL_WINDOW_RESIZABLE);
        if (gWindow == nullptr)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer
            gRenderer = SDL_CreateRenderer(gWindow, nullptr);
            if (gRenderer == nullptr)
            {
                SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Setup Dear ImGui context
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO(); (void)io;
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

                // Setup Dear ImGui style
                ImGui::StyleColorsDark();

                // Setup Platform/Renderer backends
                ImGui_ImplSDL3_InitForSDLRenderer(gWindow, gRenderer);
                ImGui_ImplSDLRenderer3_Init(gRenderer);
            }
        }
    }

    return success;
}

void close()
{
    // Cleanup ImGui
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // Destroy renderer and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void render()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Create a simple hello world window
    static bool show_demo_window = false;
    static bool show_hello_window = true;
    static float clear_color[3] = { 0.0f, 0.5f, 1.0f }; // Nice blue color

    if (show_hello_window)
    {
        ImGui::Begin("Hello, World!", &show_hello_window);

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::ColorEdit3("Clear color", clear_color);

        static int counter = 0;
        if (ImGui::Button("Button"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                   1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // Show the demo window if requested
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // Rendering
    ImGui::Render();
    SDL_SetRenderDrawColor(gRenderer,
                          (Uint8)(clear_color[0] * 255),
                          (Uint8)(clear_color[1] * 255),
                          (Uint8)(clear_color[2] * 255),
                          255);
    SDL_RenderClear(gRenderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), gRenderer);
    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[])
{
    int exitCode{ 0 };

    // Initialize
    if (!init())
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        bool quit{ false };
        SDL_Event e;

        // Main loop
        while (!quit)
        {
            // Handle events
            while (SDL_PollEvent(&e))
            {
                ImGui_ImplSDL3_ProcessEvent(&e);

                if (e.type == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
            }

            // Render everything
            render();
        }
    }

    // Clean up
    close();
    return exitCode;
}
