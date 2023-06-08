#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/position.hpp"
#include "components/hit_points.hpp"

namespace Gng2D
{
struct Scene;
}

struct PlayerControlls
{
    PlayerControlls(entt::registry&);

    bool inFocusMode()  const;
    bool isPlayerAlive() const;
    void operator()();

private:
    void playerMovement();
    void boundPlayerPosition();
    void primaryFire();
    void invulnerabilityAnimation();
    void spawnBullet(Gng2D::Position, Gng2D::Velocity);
    void hpControl();

    entt::registry& reg;
    Gng2D::Scene&   scene;
    entt::entity    playerShip;
    bool            focusMode;

    HitPoints       cachedHP;
    entt::entity    hpDisplay{entt::null};
};


