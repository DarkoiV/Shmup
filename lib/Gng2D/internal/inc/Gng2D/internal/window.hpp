#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Gng2D
{
struct Window
{
    static void init(const std::string& title, int width, int height);
    static void destroy();
    
    static auto renderer() -> SDL_Renderer*;

private:
    inline static Window*   instance;

    Window(const std::string& title, int width, int height);
    ~Window();

    SDL_Window*             sdlWindow;
    SDL_Renderer*           sdlRenderer;
};
}
