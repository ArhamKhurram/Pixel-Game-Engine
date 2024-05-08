#pragma once


// Create window with SDL_Renderer graphics context
SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);

if (window == nullptr)
{
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return -1;
}

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
if (renderer == nullptr)
{
    SDL_Log("Error creating SDL_Renderer!");
    return 0;
}


