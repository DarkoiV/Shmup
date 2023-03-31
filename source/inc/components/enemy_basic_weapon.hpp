#pragma once

struct EnemyBasicWeapon
{
    EnemyBasicWeapon(unsigned cd)
        : cooldownTicks(cd) {}
    const unsigned cooldownTicks;
    unsigned remainigCooldown{0u};
};

