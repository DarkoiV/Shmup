#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

Gng2D::MovementSystem::MovementSystem(entt::registry& r)
    : reg(r)
{
}

void Gng2D::MovementSystem::operator()()
{
    updatePosition();
}


void Gng2D::MovementSystem::updatePosition()
{
    reg.view<Position, Velocity>().each([](Position& pos, Velocity& velo)
    {
        pos += velo;
    });
}
