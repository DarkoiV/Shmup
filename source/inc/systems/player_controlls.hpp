#pragma once
#include "Gng2D/types/scene.hpp"
#include "entities/player_ship.hpp"

struct PlayerControlls
{
    PlayerControlls(Gng2D::Scene& s, PlayerShip& ps)
        : scene(s)
        , playerShip(ps) {};

    void playerControlls();
    void boundPlayerPosition();

    void operator()();

private:
    Gng2D::Scene&   scene;
    PlayerShip&     playerShip;
};


