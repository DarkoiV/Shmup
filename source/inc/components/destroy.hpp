#pragma once

struct Destroy
{
    enum class Effect 
    {
        noEffect,
        spawnRedX
    };
    Destroy(Effect effect = Effect::noEffect, unsigned rt = 0)
        : effect(effect)
        , remainingTicks(rt) {}

    Effect      effect;
    unsigned    remainingTicks;
};

