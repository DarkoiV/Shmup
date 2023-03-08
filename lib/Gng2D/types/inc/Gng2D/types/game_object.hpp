#pragma once
#include "entt/entity/registry.hpp"

namespace Gng2D
{
struct Scene;
struct GameObject
{
    GameObject(Gng2D::Scene&);
    GameObject(Gng2D::Scene&, entt::entity id);
    virtual ~GameObject() = default;
    
    entt::entity getId() const;

    template<typename Component, typename... Args>
        requires(std::is_empty<Component>::value)
    void addComponent(Args&&... args)
    {
        registry.emplace<Component>(id, std::forward<Args>(args)...);
    }

    template<typename Component, typename... Args>
        requires(not std::is_empty<Component>::value)
    Component& addComponent(Args&&... args)
    {
        return registry.emplace<Component>(id, std::forward<Args>(args)...);
    }

    template<typename Component>
    auto& getComponent()
    {
        return registry.get<Component>(id);
    }

protected:
    entt::registry&     registry;
    const entt::entity  id;
};
}

