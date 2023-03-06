#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/collider_renderer_system.hpp"
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/types/scene.hpp"
#include "entities/bullet.hpp"
#include "entities/player_ship.hpp"
#include "systems/bullet_bullet_collision.hpp"
#include "systems/entity_cleaner.hpp"
#include "systems/focus_mode_text_renderer.hpp"
#include "systems/player_bullet_collision.hpp"
#include "systems/player_controlls.hpp"
#include "systems/player_weapons.hpp"

struct FlightScene : Gng2D::Scene
{
    FlightScene();

    void onEnter()              override;
    void onExit()               override;
    bool isCompleted()          override;
    void update()               override;
    void render(SDL_Renderer*)  override;

private:
    PlayerShip              playerShip = spawnObject<PlayerShip>();
    PlayerWeapons           playerWeapons{*this, playerShip};
    PlayerControlls         playerControlls{*this, playerShip};

    Gng2D::MovementSystem   movement{*this};

    Gng2D::ColliderRendererSystem<PlayerShip::Collider>
        playerColliderRenderer{*this};
    FocusModeTextRenderer
        focusModeTextRenderer{*this};

    PlayerBulletCollision
        playerBulletCollision{*this};
    BulletBulletCollision
        bulletBulletCollision{*this};

    EntityCleaner       entityCleaner{*this};
};

