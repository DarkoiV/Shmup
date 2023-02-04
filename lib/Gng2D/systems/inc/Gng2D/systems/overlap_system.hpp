#pragma once
#include <type_traits>
#include <cmath>
#include <functional>
#include "entt/entity/registry.hpp"

namespace Gng2D
{
struct CircleCollider;
struct Position;

template<typename C>
concept CircleColliderType = std::is_base_of<CircleCollider, C>::value;

template<CircleColliderType A, CircleColliderType B>
struct OverlapSystem
{
    using OnOverlapHandler = std::function<void(entt::entity, entt::entity)>;

    OverlapSystem(entt::registry& r, OnOverlapHandler ooh)
        : registry(r)
        , onOverlap(ooh)
    {};

    void operator()()
    {
        auto colliderAView = registry.view<Position, A>();
        auto colliderBView = registry.view<Position, B>();
        for (const auto& [enttityA, posA, colliderA] : colliderAView.each())
        {
            for (const auto& [enttityB, posB, colliderB] : colliderBView.each())
            {
                auto sqrDistance = V2d::sqrDistance(posA, posB);
                auto sqrRadius = std::pow(colliderA.radius + colliderB.radius, 2);
                if (sqrDistance < sqrRadius)
                {
                    onOverlap(enttityA, enttityB);
                }
            }
        }
    }

private:
    entt::registry&     registry;
    OnOverlapHandler    onOverlap;
};
}
