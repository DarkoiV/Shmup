#pragma once
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"

namespace Gng2D
{
struct EntityRenderer
{
    EntityRenderer(entt::registry&);
    EntityRenderer(EntityRenderer&)                 = delete;
    EntityRenderer(EntityRenderer&&)                = delete;
    EntityRenderer& operator= (EntityRenderer&)     = delete;
    EntityRenderer& operator= (EntityRenderer&&)    = delete;
    ~EntityRenderer();

    void operator()(SDL_Renderer*);
    void markForSorting();

private:
    void    sortRenderables();

    entt::registry& reg;
    bool            needsSorting{false};

    using RenderableGroup = decltype(reg.group<Sprite, Position>());
    RenderableGroup     renderables{reg.group<Sprite, Position>()};
};
}

