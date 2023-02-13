#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/systems/collider_renderer_system.hpp"
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/game_object.hpp"
#include "player_ship.hpp"
#include "systems/player_bullet_collision.hpp"
#include "systems/bullet_bullet_collision.hpp"
#include "systems/player_weapons.hpp"
#include "bullet.hpp"

struct FlightScene : Gng2D::Scene
{
    void onEnter()      override;
    void onExit()       override;
    bool isCompleted()  override;
    void update()       override;
    void render()       override;

private:
    void playerControlls();
    void boundPlayerPosition();

    PlayerShip              playerShip = spawnObject<PlayerShip>();
    PlayerWeapons           playerWeapons{*this, playerShip};
    Gng2D::MovementSystem   movement{*this};

    Gng2D::ColliderRendererSystem<PlayerShip::Collider>
        playerColliderRenderer{*this};
    Gng2D::ColliderRendererSystem<EnemyBullet::Collider>
        enemyBulletColliderRenderer{*this};
    Gng2D::ColliderRendererSystem<AllyBullet::Collider>
        allyBulletColliderRenderer{*this};

    PlayerBulletCollision
        playerBulletCollision{*this};
    BulletBulletCollision
        bulletBulletCollision{*this};
};
