#pragma once
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/types/game_object.hpp"
#include "sprite_sheets.hpp"

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
            auto& sprite = ship.getComponent<Gng2D::Sprite>();
            EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Flashing, sprite);
        }
        co_yield Gng2D::Coroutine::WaitTicks{7};
        {
            auto& sprite = ship.getComponent<Gng2D::Sprite>();
            EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Normal, sprite);
        }
    }
};

