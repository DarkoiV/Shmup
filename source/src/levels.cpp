#include "levels.hpp"
#include <memory>
#include "systems/entity_factory.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/components/velocity.hpp"

using namespace Gng2D;

Coroutine levelOne(entt::registry& reg)
{
    constexpr auto D_DIR    = Velocity{0.0f, 2.0f};
    constexpr auto DR_DIR   = Velocity{1.41f, 1.41f};
    constexpr auto DL_DIR   = Velocity{-1.41f, 1.41f};

    co_yield Coroutine::Wait{10_seconds};

    // Sparrows going down
    EntityFactory(reg).spawnSparrow({320.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};
    
    EntityFactory(reg).spawnSparrow({120.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    EntityFactory(reg).spawnSparrow({520.0f, 0.0f});
    co_yield Coroutine::Wait{5_seconds};

    //Pick Up Drones
    EntityFactory(reg).spawnPickup({320.0f, 0.0f}, Pickup::Type::drones);
    co_yield Coroutine::Wait{1_seconds};
    
    // Turret Boat
    EntityFactory(reg).spawnTurretBoat({170.0f, 0.0f}, 90);
    co_yield Coroutine::Wait{1_seconds};

    EntityFactory(reg).spawnTurretBoat({470.0f, 0.0f}, 90);
    co_yield Coroutine::Wait{4_seconds};

    // LASER SPARROW
    EntityFactory(reg).spawnLaserSparrow({570.0f, 0.0f}, 155);
    co_yield Coroutine::Wait{1_seconds};
    
    EntityFactory(reg).spawnLaserSparrow({30.0f, 0.0f}, 35);
    co_yield Coroutine::Wait{13_seconds};

    // Bullets
    for (int i = 0; i < 10; ++i)
    {
        EntityFactory(reg).spawnEnemyBullet({320.0f, 0.0f}, D_DIR);
        EntityFactory(reg).spawnEnemyBullet({120.0f, 0.0f}, DR_DIR);
        co_yield Coroutine::Wait{20};

        EntityFactory(reg).spawnEnemyBullet({400.0f, 0.0f}, D_DIR);
        co_yield Coroutine::Wait{20};

        EntityFactory(reg).spawnEnemyBullet({240.0f, 0.0f}, D_DIR);
        EntityFactory(reg).spawnEnemyBullet({520.0f, 0.0f}, DL_DIR);
        co_yield Coroutine::Wait{20};
    }
    co_yield Coroutine::Wait{10};

    // -> RIGHT
    EntityFactory(reg).spawnSparrow({0.0f, 100.0f}, 0);
    co_yield Coroutine::Wait{3_seconds};

    EntityFactory(reg).spawnSparrow({0.0f, 200.0f}, 0);
    co_yield Coroutine::Wait{3_seconds};

    EntityFactory(reg).spawnSparrow({0.0f, 300.0f}, 0);
    co_yield Coroutine::Wait{5_seconds};

    // <- LEFT
    EntityFactory(reg).spawnSparrow({640.0f, 130.0f}, 180);
    co_yield Coroutine::Wait{3_seconds};

    EntityFactory(reg).spawnSparrow({640.0f, 230.0f}, 180);
    co_yield Coroutine::Wait{3_seconds};

    EntityFactory(reg).spawnSparrow({640.0f, 330.0f}, 180);
    co_yield Coroutine::Wait{5_seconds};

    // Cross
    EntityFactory(reg).spawnSparrow({0.0f, 0.0f}, 45);
    co_yield Coroutine::Wait{1_seconds};
    EntityFactory(reg).spawnSparrow({640.0f, 0.0f}, 135);
}

