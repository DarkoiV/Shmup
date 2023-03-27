#pragma once

struct EnemyBasicWeapon
{
    constexpr static unsigned cooldownTicks{50u};
    unsigned remainigCooldown{0u};
};

