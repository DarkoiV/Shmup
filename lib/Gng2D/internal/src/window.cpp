#include "Gng2D/internal/window.hpp"
#include "Gng2D/core/log.hpp"

void Gng2D::Window::init(const std::string& title, int width, int height)
{
    if (not instance) instance = new Window(title, width, height);
    else LOG::WARN("Call to window init when instance exist might result in renderer pointer invalidation, aborting");
}

void Gng2D::Window::destroy()
{
    if (instance) 
    {
        delete instance;
        instance = nullptr;
    }
}

Gng2D::Window::Window(const std::string& title, int width, int height)
{
    LOG::INFO("Creating Gng2D Window");

    LOG::INFO("Initializing SDL2 Video");
    auto err = SDL_Init(SDL_INIT_VIDEO);
    if (err) LOG::FATAL("Could not initialize SDL2 Video", SDL_GetError());

    LOG::INFO("Creating SDL2 Window");
    sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
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

auto Gng2D::Window::renderer() -> SDL_Renderer*
{
    return instance->sdlRenderer;
}
