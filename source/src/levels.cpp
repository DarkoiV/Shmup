#include "levels.hpp"
#include <memory>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/gui/text.hpp"
#include "Gng2D/gui/text_animations.hpp"
#include "entities/bullet.hpp"
#include "entities/sparrow.hpp"

using namespace Gng2D;

Coroutine levelOne(Scene& scene, FlightSceneGui& gui)
{
    gui.addPopUpText("LEVEL ONE");
    co_yield Coroutine::Wait{10_seconds};

    scene.spawnObject<Sparrow>(Position{320.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};
    
    scene.spawnObject<Sparrow>(Position{120.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    scene.spawnObject<Sparrow>(Position{520.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    for (int i = 0; i < 10; ++i)
    {
        constexpr auto D_DIR    = Velocity{0.0f, 2.0f};
        constexpr auto DR_DIR   = Velocity{1.41f, 1.41f};
        constexpr auto DL_DIR   = Velocity{-1.41f, 1.41f};
        scene.spawnObject<EnemyBullet>(Position{320.0f, 0.0f}, D_DIR);
        scene.spawnObject<EnemyBullet>(Position{120.0f, 0.0f}, DR_DIR);
        co_yield Coroutine::Wait{20};

        scene.spawnObject<EnemyBullet>(Position{400.0f, 0.0f}, D_DIR);
        co_yield Coroutine::Wait{20};

        scene.spawnObject<EnemyBullet>(Position{240.0f, 0.0f}, D_DIR);
        scene.spawnObject<EnemyBullet>(Position{520.0f, 0.0f}, DL_DIR);
        co_yield Coroutine::Wait{20};
    }
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            const float degrees = (10 * i) % 360 + (j * 40);
            const auto velocity = Velocity{V2d::rot(degrees, 2.0f)};
            scene.spawnObject<EnemyBullet>(Position{320.0f, 55.0f}, velocity);
        }
        co_yield Coroutine::Wait{3};
    }
}

