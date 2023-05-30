#pragma once

struct EnemyTargetingTurret
{
    EnemyTargetingTurret(unsigned cd)
        : cooldownTicks(cd) {}
    const unsigned cooldownTicks;
    unsigned remainigCooldown{0u};

    constexpr static unsigned rotationCooldown{10u};
    unsigned remainingRotationCooldown{0u};
};

