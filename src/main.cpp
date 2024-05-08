#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>

#include <vector>
#include <iostream>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

// Structure to represent a rectangle object
struct Rectangle {
    float x;
    float y;
    float width;
    float height;
};

// Main code
int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    #include "game.h"

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // List to store rectangle objects
    std::vector<Rectangle> rectangles;

    // Main loop
    bool done = false;
    bool showImguiWindow = false; // Flag to control visibility of the additional ImGui window
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Define window size
        int windowWidth = 1280;
        int windowHeight = 720;

        // Define the size of SDL-rendered and ImGui-rendered sections
        int sdlWidth = windowWidth * 2 / 3;
        int imguiWidth = windowWidth - sdlWidth;

        // Clear the screen
        /*SDL_RenderClear(renderer);*/


        // Render SDL content (left 2/3 of the screen)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
        SDL_Rect sdlRect = { 0, 0, sdlWidth, windowHeight };
        SDL_RenderFillRect(renderer, &sdlRect);

        // Render existing rectangles
        SDL_SetRenderDrawColor(renderer, 0, 120, 0, 255); // Green color for rectangles
        for (const auto& rect : rectangles) {
            SDL_Rect sdlRect = { static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.width), static_cast<int>(rect.height) };
            SDL_RenderFillRect(renderer, &sdlRect);
        }

        //// Movement logic for the single rectangle using arrow keys
        //const Uint8* keys = SDL_GetKeyboardState(NULL);
        //if (keys[SDL_SCANCODE_UP]) {
        //    playerRect.y -= 1;
        //}
        //if (keys[SDL_SCANCODE_DOWN]) {
        //    playerRect.y += 1;
        //}
        //if (keys[SDL_SCANCODE_LEFT]) {
        //    playerRect.x -= 1;
        //}
        //if (keys[SDL_SCANCODE_RIGHT]) {
        //    playerRect.x += 1;
        //}

        // Render ImGui content (right 1/3 of the screen)
        ImGui::SetNextWindowPos(ImVec2(sdlWidth, 0));
        ImGui::SetNextWindowSize(ImVec2(imguiWidth, windowHeight));
        ImGui::Begin("ImGui Content", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Hello from ImGui!");

        // Button to create a new rectangle
        if (ImGui::Button("Create New Rectangle")) {
            rectangles.push_back({ 200.0f, 200.0f, 50.0f, 50.0f }); // Add a new rectangle with default values
        }

        // Display movement sliders for each rectangle
        for (size_t i = 0; i < rectangles.size(); ++i) {
            auto& rect = rectangles[i];
            ImGui::Text("Rectangle %zu", i + 1);

            // Use PushID and PopID to ensure each slider has a unique identifier
            ImGui::PushID(static_cast<int>(i));

            ImGui::SliderFloat("X Position", &rect.x, 0.0f, static_cast<float>(sdlWidth));
            ImGui::SliderFloat("Y Position", &rect.y, 0.0f, static_cast<float>(windowHeight));

            ImGui::PopID();
        }

        // Additional ImGui window covering the same size as the SDL-rendered section
        if (showImguiWindow)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(sdlWidth, windowHeight));
            ImGui::Begin("Additional ImGui Window", &showImguiWindow, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Text("This is another ImGui window!");
            ImGui::End();
        }

        ImGui::End();


        // Toggle visibility of the additional ImGui window when Tab key is pressed
        if (ImGui::IsKeyPressed(ImGuiKey_Tab))
            showImguiWindow = !showImguiWindow;

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    // Cleanup
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
