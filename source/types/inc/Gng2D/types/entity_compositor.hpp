#pragma once
#include <entt/entt.hpp>
#include <functional>

namespace Gng2D
{
struct EntityCompositor
{
    EntityCompositor(entt::registry& r)
        : reg(r)
        , entity(r.create()) {}

    template<typename Component, typename... Args>
    EntityCompositor& with(Args&&... args)
    {
        reg.emplace<Component>(entity, std::forward<Args>(args)...);
        return *this;
    }

    template<typename Component>
    EntityCompositor& modify(std::function<void(Component&, entt::registry&, entt::entity)> func)
    {
        auto& comp = reg.get<Component>(entity);
        func(comp, reg, entity);
        return *this;
    }

    template<typename Component>
    EntityCompositor& modify(std::function<void(Component&)> func)
    {
        auto& comp = reg.get<Component>(entity);
        func(comp);
        return *this;
    }

    EntityCompositor& withParent(entt::entity parent);

    entt::entity get()
    {
        return entity;
    }

private:
    entt::registry& reg;
    entt::entity    entity;
};
}

