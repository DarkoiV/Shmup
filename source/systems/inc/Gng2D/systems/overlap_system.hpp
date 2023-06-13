#pragma once
#include <cmath>
#include <entt/entt.hpp>
#include "Gng2D/components/colider.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/roation.hpp"

namespace Gng2D
{
template<ColliderType A, ColliderType B>
struct OverlapSystem
{
    OverlapSystem(entt::registry& r)
        : reg(r)
    {};

    struct Reverse{};

    void operator()()
    {
        if constexpr (CircleColliderType<A> and CircleColliderType<B>)
        {
            CircleOnCircle();
        }
        else if constexpr (CircleColliderType<A> and CapsuleColliderType<B>)
        {
            CircleOnCapsule();
        }
        else if constexpr (CapsuleColliderType<A> and CircleColliderType<B>)
        {
            CircleOnCapsule<Reverse>();
        }
        else 
        {
            []<bool flag = false>()
                {static_assert(flag, "Collision not yet supported");}();
        }
    }

    virtual void onOverlap(entt::entity, entt::entity) = 0;

protected:
    entt::registry& reg;

    void CircleOnCircle()
    {
        for (const auto& [entityA, posA, colliderA] : reg.view<Position, A>().each())
        {
            for (const auto& [entityB, posB, colliderB] : reg.view<Position, B>().each())
            {
                auto sqrDistance    = V2d::sqrDistance(posA, posB);
                auto sqrRadius      = std::pow(colliderA.radius + colliderB.radius, 2);
                if (sqrDistance < sqrRadius)
                {
                    onOverlap(entityA, entityB);
                    if (not reg.valid(entityA)) break;
                }
            }
        }
    }

    template<typename R = void>
        requires std::is_same_v<R, Reverse> or std::is_same_v<R, void>
    void CircleOnCapsule()
    {
        for (const auto& [entityA, posA, colliderA] : reg.view<Position, A>().each())
        {
            for (const auto& [entityB, posB, colliderB] : reg.view<Position, B>().each())
            {
                double rotB = 0.0; 
                if (auto* rotComp = reg.try_get<Rotation>(entityB))
                {
                    rotB = rotComp->angle;
                }
                const V2d capsuleVector     = V2d::rot(rotB, colliderB.length);
                const V2d capsuleBegin      = posB - (capsuleVector/2);
                const V2d circleToCapsule   = V2d{posA.x - capsuleBegin.x, posA.y - capsuleBegin.y};

                const float t 
                    = std::max(0, 
                               std::min(colliderB.length, 
                                        V2d::dot(capsuleBegin, circleToCapsule))) 
                        / colliderB.length;

                const V2d closestCircleOnCapsule{capsuleBegin.x + t * capsuleVector.x,
                                                 capsuleBegin.y + t * capsuleVector.y};

                auto sqrDistance    = V2d::sqrDistance(posA, closestCircleOnCapsule);
                auto sqrRadius      = std::pow(colliderA.radius + colliderB.radius, 2);

                if (sqrDistance < sqrRadius)
                {
                    if constexpr (std::is_same_v<R, Reverse>) onOverlap(entityB, entityA);
                    else onOverlap(entityA, entityB);
                    if (not reg.valid(entityA)) break;
                }
            }
        }
    }
};

}

#define GNG2D_OVERLAP(NAME, ColliderA, ColliderB) \
    struct NAME : Gng2D::OverlapSystem<ColliderA, ColliderB> \
{ \
    NAME(entt::registry& r) : Gng2D::OverlapSystem<ColliderA, ColliderB>(r) {} \
    void onOverlap(entt::entity, entt::entity) override; \
} 

