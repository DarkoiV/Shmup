#include "Gng2D/systems/seq_control.hpp"
#include "Gng2D/types/scene.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/velocity.hpp"
#include "entities/bullet.hpp"

struct Level1 : Gng2D::SeqControl
{
    Level1(Gng2D::Scene& s)
        : Gng2D::SeqControl(coroutine())
        , scene(s){};

    Coroutine coroutine()
    {
        Gng2D::LOG::INFO("Hewwo! xD");
        while (true)
        {
            spawn_1();
            co_yield WaitTicks{20};
            spawn_2();
            co_yield WaitTicks{20};
            spawn_3();
            co_yield WaitTicks{20};
        }
    }

    void spawn_1()
    {
        Gng2D::LOG::INFO("SPAWN 1");
        scene.spawnObject<EnemyBullet>(Gng2D::Position{320.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
        scene.spawnObject<EnemyBullet>(Gng2D::Position{120.0f, 0.0f}, Gng2D::Velocity{1.41f, 1.41f});
    }

    void spawn_2()
    {
        Gng2D::LOG::INFO("SPAWN 2");
        scene.spawnObject<EnemyBullet>(Gng2D::Position{400.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
    }

    void spawn_3()
    {
        Gng2D::LOG::INFO("SPAWN 3");
        scene.spawnObject<EnemyBullet>(Gng2D::Position{240.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
        scene.spawnObject<EnemyBullet>(Gng2D::Position{520.0f, 0.0f}, Gng2D::Velocity{-1.41f, 1.41f});
    }
private:
    Gng2D::Scene& scene;

};

