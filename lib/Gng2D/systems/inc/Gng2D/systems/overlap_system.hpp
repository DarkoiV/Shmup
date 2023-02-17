#pragma once
#include <cmath>
#include "Gng2D/types/scene.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/position.hpp"

namespace Gng2D
{
template<CircleColliderType A, CircleColliderType B>
struct OverlapSystem
{
    OverlapSystem(Gng2D::Scene& s)
        : scene(s)
    {};

    void operator()()
    {
        for (const auto& [enttityA, posA, colliderA] : scene.view<Position, A>())
        {
            for (const auto& [enttityB, posB, colliderB] : scene.view<Position, B>())
            {
                auto sqrDistance = V2d::sqrDistance(posA, posB);
                auto sqrRadius = std::pow(colliderA.radius + colliderB.radius, 2);
                if (sqrDistance < sqrRadius)
                {
                    onOverlap(enttityA, enttityB);
                    if (not scene.entityExists(enttityA)) break;
                }
            }
        }
    }

    virtual void onOverlap(entt::entity, entt::entity) = 0;

protected:
    Gng2D::Scene&     scene;
};
}
