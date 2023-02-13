#pragma once
#include <deque>
#include <memory>
#include <entt/entity/registry.hpp>
#include "SDL2/SDL.h"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/components/game_object.hpp"

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

    template<typename Obj, typename... Args>
        requires(std::is_base_of<GameObject, Obj>::value)
    Obj spawnObject(Args&&... args)
    {
        return Obj(registry, std::forward<Args>(args)...);
    }

    bool isKeyPressed(SDL_Scancode) const;

protected:
    entt::registry              registry;
    SceneRegistry               sceneRegistry;
    SDL_Renderer*               sceneRenderer;
};

}

