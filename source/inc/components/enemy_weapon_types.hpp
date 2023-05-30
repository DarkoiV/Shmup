#pragma once

struct EnemyVulcan
{
    EnemyVulcan(unsigned cd)
        : cooldownTicks(cd) {}
    const unsigned cooldownTicks;
    unsigned remainigCooldown{0u};
};

struct EnemyTargeting
{
    EnemyTargeting(unsigned cd)
        : rotationCooldown(cd) {}
    unsigned rotationCooldown;
    unsigned remainingRotationCooldown{0u};
};

