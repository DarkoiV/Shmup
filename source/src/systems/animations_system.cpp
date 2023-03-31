#include "systems/animations_system.hpp"
#include "components/flashing_enemy.hpp"

void AnimationsSystem::operator()()
{
    for (const auto& [_, flashing] : scene.view<FlashingEnemy>())
    {
        flashing();
    }
}

