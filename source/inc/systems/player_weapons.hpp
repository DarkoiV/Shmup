#pragma once
#include "Gng2D/types/scene.hpp"
#include "entities/player_ship.hpp"

struct PlayerWeapons
{
    PlayerWeapons(Gng2D::Scene& s, PlayerShip ps)
        : scene(s)
        , playerShip(ps) {}

    void primaryFire();

    void operator()();

    int cooldownFrames      = 20;
    int remainingCooldown   = 0;

private:
    Gng2D::Scene&   scene;
    PlayerShip      playerShip;
};

