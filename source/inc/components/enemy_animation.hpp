#pragma once
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/types/game_object.hpp"
#include "sprite_sheets.hpp"

struct EnemyAnimation
{
    enum class Type 
    {
        flash
    };

    EnemyAnimation(Gng2D::GameObject go, Type t);

    void operator()()
    {
        animation();
    }

private:
    Gng2D::Coroutine animation;
};

