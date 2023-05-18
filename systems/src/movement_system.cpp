#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

Gng2D::MovementSystem::MovementSystem(Gng2D::Scene& s)
    : scene(s)
{
}

void Gng2D::MovementSystem::operator()()
{
    updatePosition();
}


void Gng2D::MovementSystem::updatePosition()
{
    for(const auto& [_, velocity, position] : scene.view<Velocity, Position>().each())
    {
        position += velocity;
    }
}
