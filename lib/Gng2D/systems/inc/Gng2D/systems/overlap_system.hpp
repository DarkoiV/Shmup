#pragma once
#include <cmath>
#include "entt/entity/registry.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/position.hpp"

namespace Gng2D
{
template<CircleColliderType A, CircleColliderType B>
struct OverlapSystem
{
    OverlapSystem(entt::registry& r)
        : registry(r)
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

    virtual void onOverlap(entt::entity, entt::entity) = 0;

protected:
    entt::registry&     registry;
};
}
