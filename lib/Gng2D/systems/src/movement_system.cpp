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
    updatePosition();
}


void Gng2D::MovementSystem::updatePosition()
{
    auto view = registry.view<Velocity, Position>();
    for(const auto& [_, velocity, position] : view.each())
    {
        position += velocity;
    }
}
