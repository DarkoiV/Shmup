#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/collider_renderer.hpp"
#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/types/scene.hpp"
#include "components/colliders.hpp"
#include "systems/enemy_bullet_spawner.hpp"
#include "systems/entity_cleaner.hpp"
#include "systems/player_controlls.hpp"

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
    PlayerControlls                             playerControlls{*this, enttRegistry};
    entt::entity                                player{getEntity("Player")};
    EnemyBulletSpawner                          enemyBulletSpawner{enttRegistry};
    Gng2D::MovementSystem                       movement{enttRegistry};
    Gng2D::GuiSystem                            guiSystem{enttRegistry};
    EntityCleaner                               entityCleaner{enttRegistry};

    Gng2D::EntityRenderer                       entityRenderer{enttRegistry};
    Gng2D::ColliderRenderer<PlayerCollider>     playerColliderRenderer{enttRegistry};
};

