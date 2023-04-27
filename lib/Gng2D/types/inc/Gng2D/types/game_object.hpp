#pragma once
#include "entt/entity/registry.hpp"
#include "Gng2D/components/tag.hpp"

namespace Gng2D
{
struct Scene;
struct GameObject
{
    GameObject(Gng2D::Scene&);
    GameObject(Gng2D::Scene&, entt::entity id);
    virtual ~GameObject() = default;
    
    entt::entity    getId() const;
    bool            isValid() const;

    template<typename T>
        requires(std::is_base_of<GameObject, T>::value)
    bool is() const
    {
        return hasComponents<Tag<T>>;
    }

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

    template<typename Component, typename... Args>
        requires(std::is_empty<Component>::value)
    void addOrReplaceComponent(Args&&... args)
    {
        registry.emplace_or_replace<Component>(id, std::forward<Args>(args)...);
    }

    template<typename Component, typename... Args>
        requires(not std::is_empty<Component>::value)
    Component& addOrReplaceComponent(Args&&... args)
    {
        return registry.emplace_or_replace<Component>(id, std::forward<Args>(args)...);
    }

    template<typename... Components>
    bool hasComponents() const
    {
        return registry.all_of<Components...>(id);
    }

    template<typename Component>
    void removeComponent()
    {
        registry.remove<Component>(id);
    }

    template<typename Component>
    auto& getComponent()
    {
        return registry.get<Component>(id);
    }

protected:
    Scene&              scene;

private:
    entt::registry&     registry;
    const entt::entity  id;
};
}

