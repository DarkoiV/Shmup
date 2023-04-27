#include "components/enemy_animation.hpp"

static Gng2D::Coroutine flashShip(Gng2D::GameObject ship)
{
    {
        auto& sprite = ship.getComponent<Gng2D::Sprite>();
        EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Flashing, sprite);
    }
    co_yield Gng2D::Coroutine::Wait{7};
    {
        auto& sprite = ship.getComponent<Gng2D::Sprite>();
        EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Normal, sprite);
    }
}

EnemyAnimation::EnemyAnimation(Gng2D::GameObject go, Type t)
{
    switch(t)
    {
        case Type::flash:
            animation = Gng2D::Coroutine(flashShip, go);
            break;
    }
}
