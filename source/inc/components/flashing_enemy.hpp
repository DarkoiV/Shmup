#pragma once
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/types/game_object.hpp"

struct FlashingEnemy
{
    FlashingEnemy(Gng2D::GameObject go)
    {
        flashing = Gng2D::Coroutine(flashShip, go);
    }

    void operator()()
    {
        flashing();
    }

private:
    Gng2D::Coroutine flashing;
    static Gng2D::Coroutine flashShip(Gng2D::GameObject ship)
    {
        {
            auto& srcRect = ship.getComponent<Gng2D::Sprite>().srcRect;
            srcRect.y = srcRect.h;
        }
        co_yield Gng2D::Coroutine::WaitTicks{7};
        {
            auto& srcRect = ship.getComponent<Gng2D::Sprite>().srcRect;
            srcRect.y = 0;
        }
    }
};

