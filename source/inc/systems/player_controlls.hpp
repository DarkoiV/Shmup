#pragma once
#include "Gng2D/types/scene.hpp"
#include "entities/player_ship.hpp"

struct PlayerControlls
{
    PlayerControlls(Gng2D::Scene& s, PlayerShip ps)
        : scene(s)
        , playerShip(ps) {};

    bool inFocusMode()  const;
    void operator()();

private:
    void playerMovement();
    void boundPlayerPosition();
    void primaryFire();
    void invulnerabilityAnimation();

    Gng2D::Scene&   scene;
    PlayerShip      playerShip;
    bool            focusMode;
};


