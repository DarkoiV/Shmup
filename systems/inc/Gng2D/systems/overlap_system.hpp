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
        for (const auto& [objA, posA, colliderA] : scene.view<Position, A>().each())
        {
            for (const auto& [objB, posB, colliderB] : scene.view<Position, B>().each())
            {
                auto sqrDistance = V2d::sqrDistance(posA, posB);
                auto sqrRadius = std::pow(colliderA.radius + colliderB.radius, 2);
                if (sqrDistance < sqrRadius)
                {
                    onOverlap(objA, objB);
                    if (not objA.isValid()) break;
                }
            }
        }
    }

    virtual void onOverlap(GameObject, GameObject) = 0;

protected:
    Gng2D::Scene&     scene;
};
}
