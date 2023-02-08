#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/acceleration.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

Gng2D::MovementSystem::MovementSystem(entt::registry& r)
    : registry(r)
{
}

void Gng2D::MovementSystem::operator()()
{
    updateVelocity();
    updatePosition();
}

void Gng2D::MovementSystem::updateVelocity()
{
    auto view = registry.view<Acceleration, Velocity>();
    for (const auto& [_, acceleration, velocity] : view.each())
    {
        const auto& max = velocity.max;
        auto& value     = velocity.value;

        value += acceleration.value;
        if (value.x > max and value.x > 0) value.x = max;
        if (value.y > max and value.y > 0) value.y = max;
        if (value.x < -max and value.x < 0) value.x = -max;
        if (value.y < -max and value.y < 0) value.y = -max;
    }
}

void Gng2D::MovementSystem::updatePosition()
{
    auto view = registry.view<Velocity, Position>();
    for(const auto& [_, velocity, position] : view.each())
    {
        position.value += velocity.value;

        auto& value = velocity.value;
        value.x -= value.x * velocity.dragFactor;
        if (value.x * value.x < 0.01f) value.x = 0;
        value.y -= value.y * velocity.dragFactor;
        if (value.y * value.y < 0.01f) value.y = 0;
    }
}
