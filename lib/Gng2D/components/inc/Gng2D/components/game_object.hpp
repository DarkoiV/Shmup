#pragma once
#include "entt/entity/registry.hpp"

namespace Gng2D
{
struct GameObject
{
    GameObject(entt::registry&);
    virtual ~GameObject();
    
    auto getId() const  -> entt::entity;

protected:
    entt::registry&     registry;
    const entt::entity  id;

    template<typename Component, typename... Args>
    void addComponent(Args&&... args)
    {
        registry.emplace<Component>(id, std::forward<Args>(args)...);
    }
};
}
