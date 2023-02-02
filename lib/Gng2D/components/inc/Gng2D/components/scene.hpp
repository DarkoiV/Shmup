#pragma once
#include <deque>
#include <memory>
#include <entt/entity/registry.hpp>
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/components/game_object.hpp"

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
    using SceneObject = std::unique_ptr<GameObject>;

    entt::registry              registry;
    SDL_Renderer*               sceneRenderer;
    std::deque<SceneObject>     sceneObjects;
    SceneRegistry               sceneRegistry;
};

}

