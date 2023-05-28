#pragma once
#include <entt/entt.hpp>
#include <functional>

namespace Gng2D
{
struct EntityBuilder
{
    EntityBuilder(entt::registry& r)
        : reg(r)
        , entity(r.create()) {}

    template<typename Component, typename... Args>
    EntityBuilder& with(Args&&... args)
    {
        reg.emplace<Component>(entity, std::forward<Args>(args)...);
        return *this;
    }

    template<typename Component>
    EntityBuilder& modify(std::function<void(Component&, entt::registry&, entt::entity)> func)
    {
        auto& comp = reg.get<Component>(entity);
        func(comp, reg, entity);
        return *this;
    }

    template<typename Component>
    EntityBuilder& modify(std::function<void(Component&)> func)
    {
        auto& comp = reg.get<Component>(entity);
        func(comp);
        return *this;
    }

    EntityBuilder& withChild(entt::entity child);

    entt::entity get()
    {
        return entity;
    }

private:
    entt::registry& reg;
    entt::entity    entity;
};
}

