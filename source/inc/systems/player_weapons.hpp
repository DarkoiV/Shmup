#pragma once
#include "Gng2D/components/scene.hpp"
#include "entities/player_ship.hpp"

struct PlayerWeapons
{
    PlayerWeapons(Gng2D::Scene&, PlayerShip&);
    void primaryFire();

    void operator()();

    int cooldownFrames      = 20;
    int remainingCooldown   = 0;

private:
    Gng2D::Scene&   scene;
    PlayerShip&     playerShip;
};
