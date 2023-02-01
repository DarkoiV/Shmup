#pragma once
#include <entt/entity/registry.hpp>

struct SDL_Renderer;

namespace Gng2D
{
struct Scene
{
    Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&)      = delete;
    virtual ~Scene()    = default;

    virtual void onEnter()              = 0;
    virtual void onExit()               = 0;
    virtual bool isCompleted()          = 0;
    virtual void update()               = 0;
    virtual void render();

    void setNextScene(const std::string& name);

protected:
    entt::registry  registry;
    SDL_Renderer*   sceneRenderer;
};

}

