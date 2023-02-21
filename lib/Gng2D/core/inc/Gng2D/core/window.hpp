#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Gng2D
{
struct Window
{
    Window();
    ~Window();
    void renderFrame();
    
    SDL_Renderer*    renderer();

private:
    SDL_Window*             sdlWindow;
    SDL_Renderer*           sdlRenderer;
    uint32_t                frameEndTime{0};
};
}
