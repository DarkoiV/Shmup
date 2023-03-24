#pragma once
#include <SDL2/SDL.h>

namespace Gng2D
{
struct Scene;
struct EntityRenderer
{
    EntityRenderer(Scene&);
    EntityRenderer(EntityRenderer&)                 = delete;
    EntityRenderer(EntityRenderer&&)                = delete;
    EntityRenderer& operator= (EntityRenderer&)     = delete;
    EntityRenderer& operator= (EntityRenderer&&)    = delete;
    ~EntityRenderer();

    void operator()(SDL_Renderer*);
    void markForSorting();

private:
    void    sortRenderables();

    Scene&  scene;
    bool    needsSorting{false};
};
}

