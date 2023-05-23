#pragma once
#include <entt/entt.hpp>
#include "Gng2D/types/scene.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/position.hpp"

struct PlayerControlls
{
    PlayerControlls(Gng2D::Scene&, entt::registry&);

    bool inFocusMode()  const;
    void operator()();

private:
    void playerMovement();
    void boundPlayerPosition();
    void primaryFire();
    void invulnerabilityAnimation();
    void spawnBullet(Gng2D::Position, Gng2D::Velocity);

    Gng2D::Scene&   scene;
    entt::registry& reg;
    entt::entity    playerShip;
    bool            focusMode;
};


