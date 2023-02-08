#pragma once
#include <memory>
#include <vector>
#include "Gng2D/systems/movement_system.hpp"
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/game_object.hpp"
#include "player_ship.hpp"

struct FlightScene : public Gng2D::Scene
{
    void onEnter()      override;
    void onExit()       override;
    bool isCompleted()  override;
    void update()       override;

private:
    Gng2D::GameObject       playerShip = spawnObject<PlayerShip>();
    Gng2D::MovementSystem   movementSystem{entityRegistry};
};
