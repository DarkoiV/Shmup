#pragma once
#include <entt/entity/registry.hpp>
#include <SDL2/SDL.h>
#include "Gng2D/core/render_system.hpp"

namespace Gng2D
{

struct Scene
{
    Scene(const Scene&) = delete;
    virtual ~Scene()    = default;

    virtual void onEnter()          = 0;
    virtual void onExit()           = 0;
    virtual bool isCompleted()      = 0;
    virtual void update(SDL_Event&) = 0;

    void render();

protected:
    entt::registry  entityRegistry;
    RenderSystem    renderSystem{entityRegistry};
};

}

