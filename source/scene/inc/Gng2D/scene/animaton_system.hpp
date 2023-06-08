#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/animation.hpp"

namespace Gng2D
{
struct AnimationSystem
{
    AnimationSystem(entt::registry&);

    void operator()();

private:
    entt::registry& reg;
};
}

