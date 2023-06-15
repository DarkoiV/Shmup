#pragma once
#include <entt/entt.hpp>

struct EnemyVulcan
{
    EnemyVulcan(unsigned cd)
        : cooldownTicks(cd) {}
    const unsigned cooldownTicks;
    unsigned remainigCooldown{0u};
};

struct EnemyLaser 
{
    EnemyLaser(unsigned cd, unsigned d)
        : cooldownTicks(cd)
        , shootingDuration(d) {}

    enum Phase 
    {
        charging,
        shooting
    } phase{charging};

    const unsigned cooldownTicks;
    const unsigned shootingDuration;

    unsigned remainigPhaseTicks{cooldownTicks};

    entt::entity chargeMarker{entt::null};
    entt::entity laser{entt::null};
};

struct EnemyTargeting
{
    EnemyTargeting(unsigned cd)
        : rotationCooldown(cd) {}
    unsigned rotationCooldown;
    unsigned remainingRotationCooldown{0u};
};

