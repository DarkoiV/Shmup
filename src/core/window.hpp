#pragma once

#include <SDL2/SDL.h>

class Window 
{
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window*   m_window   = nullptr;

public:
    Window(int w, int h, int s);
    Window(Window&)  = delete;
    Window(Window&&) = delete;
    ~Window();

    // Get window renderer
    auto renderer() -> SDL_Renderer*;

    // Render frame
    void update();
};
