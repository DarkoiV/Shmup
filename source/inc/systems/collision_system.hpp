#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "components/colliders.hpp"

struct CollisionSystem
{
    CollisionSystem(entt::registry&);
    void operator()();

private:
    GNG2D_OVERLAP(BulletBullet,     PlayerBulletCollider,   EnemyBulletCollider)    bulletBullet;
    GNG2D_OVERLAP(PlayerEnemy,      PlayerCollider,         EnemyCollider)          playerEnemy;
    GNG2D_OVERLAP(PlayerPickup,     PlayerCollider,         PickupCollider)         playerPickup;
    GNG2D_OVERLAP(BulletEnemy,      PlayerBulletCollider,   EnemyCollider)          bulletEnemy;
    GNG2D_OVERLAP(BulletPlayer,     EnemyBulletCollider,    PlayerCollider)         bulletPlayer;
    GNG2D_OVERLAP(LaserPlayer,      EnemyLaserCollider,     PlayerCollider)         laserPlayer;
};

