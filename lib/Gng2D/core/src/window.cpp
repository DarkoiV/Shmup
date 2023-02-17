#include "Gng2D/core/settings.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Window::Window()
{
    LOG::INFO("Creating Gng2D Window");

    LOG::INFO("Initializing SDL2 Video");
    auto err = SDL_Init(SDL_INIT_VIDEO);
    if (err) LOG::FATAL("Could not initialize SDL2 Video", SDL_GetError());

    LOG::INFO("Creating SDL2 Window");
    sdlWindow = SDL_CreateWindow(TITLE.c_str(), 
                                 SDL_WINDOWPOS_CENTERED, 
                                 SDL_WINDOWPOS_CENTERED, 
                                 SCREEN_WIDTH, 
                                 SCREEN_HEIGHT, 
                                 0);
    if (not sdlWindow) LOG::FATAL("Could not create SDL2 Window", SDL_GetError());

    LOG::INFO("Creating SDL2 Renderer for window");
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (not sdlRenderer) LOG::FATAL("Could not create SDL2 Renderer", SDL_GetError());

    LOG::OK("Created Gng2D Window");
}

Gng2D::Window::~Window()
{
    LOG::INFO("Destroying Gng2D Window");
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Renderer* Gng2D::Window::renderer()
{
    return sdlRenderer;
}

void Gng2D::Window::renderFrame()
{
    SDL_RenderPresent(sdlRenderer);
    SDL_RenderClear(sdlRenderer);
    auto timeNow = SDL_GetTicks();
    auto expectedEnd = frameEndTime + (1000/FPS);
    if (expectedEnd > timeNow) SDL_Delay(expectedEnd - timeNow);
    frameEndTime = SDL_GetTicks();
}

