#pragma once
#include <SDL2/SDL.h>
#include <entt/entity/registry.hpp>

namespace Gng2D
{
struct RenderSystem
{
    RenderSystem(entt::registry&);

    void operator()() const;

private:
    entt::registry&     registry;
    SDL_Renderer*       targetRenderer;
};
}
