#pragma once
#include <SDL2/SDL.h>

namespace Gng2D
{
struct Window
{
    Window();
    ~Window();

    static auto renderer() -> SDL_Renderer*;

private:
    inline static SDL_Window*       sdlWindow;
    inline static SDL_Renderer*     sdlRenderer;
};
}
