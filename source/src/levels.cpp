#include "levels.hpp"
#include <memory>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

using namespace Gng2D;

static void popLevelText(Scene& scene, const std::string& text)
{
    // auto levelText = scene.spawn<TextObject>(Gng2D::Position{SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f},
    //                                         "charmap-oldschool_white",
    //                                         text,
    //                                         3u);
    // levelText.addComponent<TimedExistence>(5_seconds);
}

Coroutine levelOne(Scene& scene, EntityFactory& factory)
{
    popLevelText(scene, "LEVEL ONE");
    co_yield Coroutine::Wait{5_seconds};

    factory.spawnSparrow({320.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};
    
    factory.spawnSparrow({120.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    factory.spawnSparrow({520.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    for (int i = 0; i < 10; ++i)
    {
        constexpr auto D_DIR    = Velocity{0.0f, 2.0f};
        constexpr auto DR_DIR   = Velocity{1.41f, 1.41f};
        constexpr auto DL_DIR   = Velocity{-1.41f, 1.41f};
        factory.spawnEnemyBullet({320.0f, 0.0f}, D_DIR);
        factory.spawnEnemyBullet({120.0f, 0.0f}, DR_DIR);
        co_yield Coroutine::Wait{20};

        factory.spawnEnemyBullet({400.0f, 0.0f}, D_DIR);
        co_yield Coroutine::Wait{20};

        factory.spawnEnemyBullet({240.0f, 0.0f}, D_DIR);
        factory.spawnEnemyBullet({520.0f, 0.0f}, DL_DIR);
        co_yield Coroutine::Wait{20};
    }
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            const float degrees = (10 * i) % 360 + (j * 40);
            const auto velocity = Velocity{V2d::rot(degrees, 2.0f)};
            factory.spawnEnemyBullet({320.0f, 55.0f}, velocity);
        }
        co_yield Coroutine::Wait{3};
    }
}

