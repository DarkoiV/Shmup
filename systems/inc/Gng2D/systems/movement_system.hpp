#pragma once
#include <entt/entt.hpp>

namespace Gng2D
{
struct MovementSystem
{
    MovementSystem(entt::registry&);
    void operator()();

protected:
    void updatePosition();

    entt::registry& reg;
};
}
