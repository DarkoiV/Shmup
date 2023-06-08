#pragma once
#include <memory>
#include <vector>
#include <iterator>
#include <tuple>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "Gng2D/systems/animaton_system.hpp"
#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/systems/position_system.hpp"

namespace Gng2D
{
struct Scene
{
    Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&)      = delete;
    virtual ~Scene();

    auto operator=(Scene&)  = delete;
    auto operator=(Scene&&) = delete;

    virtual void onEnter()              = 0;
    virtual void onExit()               = 0;
    virtual bool isCompleted()          = 0;
    virtual void update()               = 0;
    virtual void render(SDL_Renderer*)  = 0;

    virtual void onKeyDown(SDL_KeyboardEvent&)  {};
    virtual void onKeyUp(SDL_KeyboardEvent&)    {};

    void operator()();
    bool isPaused()     const;

    template<typename Coro, typename... Args>
    void addCoroutine(Coro coro, Args&&... args)
    {
        coroutines.emplace_back(coro, std::forward<Args>(args)...);
    }

    bool        isKeyPressed(SDL_Scancode) const;

    EntityCompositor   newEntity();
    entt::entity    getEntity(const std::string&);

protected:
    bool                pause{false};
    entt::registry      reg;

    AnimationSystem     animationSystem{reg};
    EntityRenderer      entityRenderer{reg};
    GuiSystem           guiSystem{reg};
    PositionSystem      positionSystem{reg};

private:
    void                    runCoroutines();
    std::vector<Coroutine>  coroutines;

    using NamedEntities = std::unordered_map<std::string, entt::entity>;
    NamedEntities   namedEntities;
    void            addNamedEntity(entt::registry&, entt::entity);
    void            removeNamedEntity(entt::registry&, entt::entity);

    static void addChildToParent(entt::registry&, entt::entity);
    static void removeChildFromParent(entt::registry&, entt::entity);
    static void destroyAllChildren(entt::registry&, entt::entity);
    static void updateChildrenLayer(entt::registry&, entt::entity);
};
}

