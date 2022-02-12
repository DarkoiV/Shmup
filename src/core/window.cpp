#include "window.hpp"
#include "log.hpp"

Window::Window(int w, int h, int s) 
{
    // Init SDL video
    LOG::INFO("Initializing SDL video");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        LOG::FATAL("Failed to initialize SDL video", SDL_GetError());
    }
    LOG::OK("SDL video initialized");

    // Create SDL window
    LOG::INFO("Creating SDL window");
    m_window = SDL_CreateWindow
    (
        "SHMUP", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w * s,
        h * s, 
        0
    );

    if (m_window == nullptr) 
    {
        LOG::FATAL("Failed to create SDL Window", SDL_GetError());
    }
    LOG::OK("SDL window created");

    // Create window renderer
    LOG::INFO("Creating window's renderer");
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr) 
    {
        LOG::FATAL("Failed to create window's renderer", SDL_GetError());
    }
    SDL_RenderSetLogicalSize(m_renderer, w, h);
    LOG::OK("Window's renderer created");
}

Window::~Window() 
{
    LOG::INFO("Destroying window and renderer");
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

auto Window::renderer() -> SDL_Renderer* 
{
    return m_renderer;
}
