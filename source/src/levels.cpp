#include "levels.hpp"
#include <memory>
#include "systems/entity_factory.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"

using namespace Gng2D;

Coroutine levelOne(entt::registry& reg)
{
    co_yield Coroutine::Wait{5_seconds};

    EntityFactory(reg).spawnSparrow({320.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};
    
    EntityFactory(reg).spawnSparrow({120.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    EntityFactory(reg).spawnSparrow({520.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    for (int i = 0; i < 10; ++i)
    {
        constexpr auto D_DIR    = Velocity{0.0f, 2.0f};
        constexpr auto DR_DIR   = Velocity{1.41f, 1.41f};
        constexpr auto DL_DIR   = Velocity{-1.41f, 1.41f};
        EntityFactory(reg).spawnEnemyBullet({320.0f, 0.0f}, D_DIR);
        EntityFactory(reg).spawnEnemyBullet({120.0f, 0.0f}, DR_DIR);
        co_yield Coroutine::Wait{20};

        EntityFactory(reg).spawnEnemyBullet({400.0f, 0.0f}, D_DIR);
        co_yield Coroutine::Wait{20};

        EntityFactory(reg).spawnEnemyBullet({240.0f, 0.0f}, D_DIR);
        EntityFactory(reg).spawnEnemyBullet({520.0f, 0.0f}, DL_DIR);
        co_yield Coroutine::Wait{20};
    }
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            const float degrees = (10 * i) % 360 + (j * 40);
            const auto velocity = Velocity{V2d::rot(degrees, 2.0f)};
            EntityFactory(reg).spawnEnemyBullet({320.0f, 55.0f}, velocity);
        }
        co_yield Coroutine::Wait{3};
    }
}

