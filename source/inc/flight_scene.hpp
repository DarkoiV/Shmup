#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/collider_renderer_system.hpp"
#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/types/scene.hpp"
#include "entities/bullet.hpp"
#include "entities/player_ship.hpp"
#include "systems/animations_system.hpp"
#include "systems/bullet_bullet_collision.hpp"
#include "systems/bullet_enemy_collision.hpp"
#include "systems/enemy_bullet_spawner.hpp"
#include "systems/entity_cleaner.hpp"
#include "systems/player_bullet_collision.hpp"
#include "systems/player_controlls.hpp"
#include "systems/player_enemy_collision.hpp"

struct FlightScene : Gng2D::Scene
{
    FlightScene();

    void onEnter()              override;
    void onExit()               override;
    bool isCompleted()          override;
    void update()               override;
    void render(SDL_Renderer*)  override;

    void onKeyDown(SDL_KeyboardEvent&) override;
    void onKeyUp(SDL_KeyboardEvent&) override;

private:
    PlayerShip              playerShip = spawn<PlayerShip>();
    PlayerControlls         playerControlls{*this, playerShip};

    AnimationsSystem
        animationSystem{*this};

    EnemyBulletSpawner
        enemyBulletSpawner{*this};

    Gng2D::MovementSystem   movement{*this};

    Gng2D::ColliderRendererSystem<PlayerShip::Collider>
        playerColliderRenderer{*this};
    Gng2D::EntityRenderer
        entityRenderer{*this};

    PlayerBulletCollision
        playerBulletCollision{*this};
    PlayerEnemyCollision 
        playerEnemyCollision{*this};
    BulletBulletCollision
        bulletBulletCollision{*this};
    BulletEnemyCollision
        bulletEnemyCollision{*this};

    EntityCleaner       entityCleaner{*this};

    struct FocusDisplay {};
};

