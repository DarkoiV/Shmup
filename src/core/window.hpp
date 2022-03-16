#pragma once

#include <SDL2/SDL.h>

class Window 
{
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window*   m_window   = nullptr;

    Window(int w, int h, int s);
    Window(Window&)  = delete;
    Window(Window&&) = delete;
    ~Window();

    inline static Window* instance = nullptr;

public:
    static void init(int w, int h, int s);
    static auto get() -> Window&;

    // Get window renderer
    auto renderer() -> SDL_Renderer*;

    // Render frame
    void update();
};
