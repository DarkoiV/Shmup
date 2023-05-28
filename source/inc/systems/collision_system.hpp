#pragma once
#include "Gng2D/systems/overlap_system.hpp"
#include "components/colliders.hpp"

struct CollisionSystem
{
    CollisionSystem(entt::registry&);
    void operator()();

private:
    struct BulletBullet 
        : Gng2D::OverlapSystem<PlayerBulletCollider, EnemyBulletCollider>
    {
        BulletBullet(entt::registry& r)
            : Gng2D::OverlapSystem<PlayerBulletCollider, EnemyBulletCollider>(r) 
        {}
        void onOverlap(entt::entity, entt::entity) override;
    } bulletBullet;

    struct PlayerEnemy 
        : Gng2D::OverlapSystem<PlayerCollider, EnemyCollider>
    {
        PlayerEnemy(entt::registry& r)
            : Gng2D::OverlapSystem<PlayerCollider, EnemyCollider>(r) 
        {}
        void onOverlap(entt::entity, entt::entity) override;
    } playerEnemy;

    struct PlayerPickup
        : Gng2D::OverlapSystem<PlayerCollider, PickupCollider>
    {
        PlayerPickup(entt::registry& r)
            : Gng2D::OverlapSystem<PlayerCollider, PickupCollider>(r)
        {}
        void onOverlap(entt::entity, entt::entity) override;
    } playerPickup;

    struct BulletEnemy
        : Gng2D::OverlapSystem<PlayerBulletCollider, EnemyCollider>
    {
        BulletEnemy(entt::registry& r)
            : Gng2D::OverlapSystem<PlayerBulletCollider, EnemyCollider>(r) 
        {}
        void onOverlap(entt::entity, entt::entity) override;
    } bulletEnemy;

    struct BulletPlayer
        : Gng2D::OverlapSystem<EnemyBulletCollider, PlayerCollider>
    {
        BulletPlayer(entt::registry& r)
            : Gng2D::OverlapSystem<EnemyBulletCollider, PlayerCollider>(r) 
        {}
        void onOverlap(entt::entity, entt::entity) override;
    } bulletPlayer;
};

