#pragma once
#include <SDL2/SDL.h>

namespace Gng2D
{
struct Window
{
    Window();
    ~Window();

    auto renderer() -> SDL_Renderer*;

private:
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
};
}
