#include "levels.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "entities/bullet.hpp"

using namespace Gng2D;

Coroutine levelOne(Scene& scene)
{
    for (int i = 1; i < 10; ++i)
    {
        constexpr auto D_DIR    = Velocity{0.0f, 2.0f};
        constexpr auto DR_DIR   = Velocity{1.41f, 1.41f};
        constexpr auto DL_DIR   = Velocity{-1.41f, 1.41f};
        scene.spawnObject<EnemyBullet>(Position{320.0f, 0.0f}, D_DIR);
        scene.spawnObject<EnemyBullet>(Position{120.0f, 0.0f}, DR_DIR);
        co_yield Coroutine::WaitTicks{20};

        scene.spawnObject<EnemyBullet>(Position{400.0f, 0.0f}, D_DIR);
        co_yield Coroutine::WaitTicks{20};

        scene.spawnObject<EnemyBullet>(Position{240.0f, 0.0f}, D_DIR);
        scene.spawnObject<EnemyBullet>(Position{520.0f, 0.0f}, DL_DIR);
        co_yield Coroutine::WaitTicks{20};
    }
}

