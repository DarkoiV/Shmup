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
struct CollisionSystem
{
    using CollisionHandler = std::function<void(entt::entity, entt::entity)>;

    CollisionSystem(entt::registry& r, CollisionHandler ch)
        : registry(r)
        , collisionHandler(ch)
    {};

    void operator()()
    {
        auto colliderAView = registry.view<Position, A>();
        auto colliderBView = registry.view<Position, B>();
        for (const auto& [enttityA, posA, colliderA] : colliderAView.each())
        {
            for (const auto& [enttityB, posB, colliderB] : colliderBView.each())
            {
                auto distance = std::sqrt(std::pow(posA.x - posB.x, 2) + std::pow(posA.y - posB.y, 2));
                if (distance < (colliderA.radius + colliderB.radius))
                {
                    collisionHandler(enttityA, enttityB);
                }
            }
        }
    }

private:
    entt::registry&     registry;
    CollisionHandler    collisionHandler;
};
}
