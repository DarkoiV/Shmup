#pragma once
#include <deque>
#include <memory>
#include <entt/entity/registry.hpp>
#include "SDL2/SDL.h"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/types/game_object.hpp"

namespace Gng2D
{
struct Application;
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
    virtual void render();

///// Entity management /////
    template<typename Obj, typename... Args>
        requires(std::is_base_of<GameObject, Obj>::value)
    Obj spawnObject(Args&&... args)
    {
        return Obj(*this, std::forward<Args>(args)...);
    }

    template<typename... Components>
    auto view()
    {
        return registry.view<Components...>().each();
    }

    GameObject  getEntity(entt::entity id);
    bool        entityExists(entt::entity id) const;
    void        destroyEntity(entt::entity id);

///// Other /////
    bool            isKeyPressed(SDL_Scancode) const;
    SDL_Renderer*   getRenderer() const;

protected:
    SceneRegistry                   sceneRegistry;

private:
    entt::registry                  registry;
    inline static SDL_Renderer*     sceneRenderer;

    friend struct ::Gng2D::Application;
    friend struct ::Gng2D::GameObject;
};

}

