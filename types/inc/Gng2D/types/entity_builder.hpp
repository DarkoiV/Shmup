#pragma once
#include <entt/entt.hpp>

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

    entt::entity get()
    {
        return entity;
    }

private:
    entt::registry& reg;
    entt::entity    entity;
};
}

