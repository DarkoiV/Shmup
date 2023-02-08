#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Gng2D
{
struct Window
{
    static void init(const std::string& title, int width, int height);
    static void destroy();
    static void renderFrame();
    
    static SDL_Renderer*    renderer();

private:
    inline static Window*   instance;

    Window(const std::string& title, int width, int height);
    ~Window();

    SDL_Window*             sdlWindow;
    SDL_Renderer*           sdlRenderer;
    uint32_t                frameEndTime{0};
    constexpr static int    FPS{60};
};
}
