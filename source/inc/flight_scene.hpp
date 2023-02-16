#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/systems/collider_renderer_system.hpp"
#include "Gng2D/types/scene.hpp"
#include "Gng2D/types/game_object.hpp"
#include "entities/player_ship.hpp"
#include "entities/bullet.hpp"
#include "systems/player_bullet_collision.hpp"
#include "systems/bullet_bullet_collision.hpp"
#include "systems/player_weapons.hpp"

struct FlightScene : Gng2D::Scene
{
    void onEnter()      override;
    void onExit()       override;
    bool isCompleted()  override;
    void update()       override;
    void render()       override;

private:
    PlayerShip              playerShip = spawnObject<PlayerShip>();
    PlayerWeapons           playerWeapons{*this, playerShip};

    void                    playerControlls();
    void                    boundPlayerPosition();
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
