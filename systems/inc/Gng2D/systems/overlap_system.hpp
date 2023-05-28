#pragma once
#include <cmath>
#include <entt/entt.hpp>
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/position.hpp"

namespace Gng2D
{
template<CircleColliderType A, CircleColliderType B>
struct OverlapSystem
{
    OverlapSystem(entt::registry& r)
        : reg(r)
    {};

    void operator()()
    {
        for (const auto& [entityA, posA, colliderA] : reg.view<Position, A>().each())
        {
            for (const auto& [entityB, posB, colliderB] : reg.view<Position, B>().each())
            {
                auto sqrDistance = V2d::sqrDistance(posA, posB);
                auto sqrRadius = std::pow(colliderA.radius + colliderB.radius, 2);
                if (sqrDistance < sqrRadius)
                {
                    onOverlap(entityA, entityB);
                    if (not reg.valid(entityA)) break;
                }
            }
        }
    }

    virtual void onOverlap(entt::entity, entt::entity) = 0;

protected:
    entt::registry& reg;
};
}

#define GNG2D_OVERLAP(NAME, ColliderA, ColliderB) \
    struct NAME : Gng2D::OverlapSystem<ColliderA, ColliderB> \
{ \
    NAME(entt::registry& r) : Gng2D::OverlapSystem<ColliderA, ColliderB>(r) {} \
    void onOverlap(entt::entity, entt::entity) override; \
} 

