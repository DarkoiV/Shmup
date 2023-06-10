#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/collider_renderer.hpp"
#include "Gng2D/scene/scene.hpp"
#include "components/colliders.hpp"
#include "systems/collision_system.hpp"
#include "systems/enemy_weapons.hpp"
#include "systems/entity_cleaner.hpp"
#include "systems/entity_factory.hpp"
#include "systems/player_controlls.hpp"

struct FlightScene : Gng2D::Scene
{
    FlightScene();

    void onEnter()              override;
    void onExit()               override;
    void update()               override;
    void render(SDL_Renderer*)  override;

    void onKeyDown(SDL_KeyboardEvent&) override;
    void onKeyUp(SDL_KeyboardEvent&) override;

private:
    PlayerControlls                             playerControlls{reg};
    EnemyWeapons                                enemyWeapons{reg};
    CollisionSystem                             collisionSystem{reg};
    EntityCleaner                               entityCleaner{reg};

    Gng2D::ColliderRenderer<PlayerCollider>     playerColliderRenderer{reg};

    void gotoGameOver();
};

