#pragma once
#include "entt/entity/registry.hpp"

namespace Gng2D
{
struct Scene;
struct GameObject
{
    GameObject(Gng2D::Scene&);
    virtual ~GameObject() = default;
    
    entt::entity getId() const;

    template<typename Component, typename... Args>
    void addComponent(Args&&... args)
    {
        registry.emplace<Component>(id, std::forward<Args>(args)...);
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
