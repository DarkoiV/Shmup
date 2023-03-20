#pragma once

struct BasicWeapon
{
    constexpr static unsigned cooldownTicks{20u};
    unsigned remainigCooldown{0u};
};

