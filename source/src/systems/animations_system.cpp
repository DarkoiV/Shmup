#include "systems/animations_system.hpp"
#include "components/enemy_animation.hpp"

void AnimationsSystem::operator()()
{
    for (const auto& [_, animation] : scene.view<EnemyAnimation>())
    {
        animation();
    }
}

