#pragma once
#include <SDL2/SDL.h>

namespace Gng2D
{
struct Scene;
struct EntityRenderer
{
    EntityRenderer(Scene&);

    void operator()(SDL_Renderer*);

private:
    Scene& scene;
};
}

