#pragma once
#include <entt/entity/registry.hpp>
#include "Gng2D/core/render_system.hpp"

namespace Gng2D
{

struct Scene
{
    Scene()             = default;
    Scene(const Scene&) = delete;
    Scene(Scene&&)      = delete;
    virtual ~Scene()    = default;

    virtual void onEnter()              = 0;
    virtual void onExit()               = 0;
    virtual bool isCompleted()          = 0;
    virtual void update()               = 0;

    void render();

private:
    entt::registry  entityRegistry;
    RenderSystem    renderSystem{entityRegistry};
};

}

