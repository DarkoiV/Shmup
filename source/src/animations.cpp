#include "animations.hpp"

Gng2D::Coroutine flashShip(entt::registry& reg, entt::entity ship)
{
    {
        auto& sprite = reg.get<Gng2D::Sprite>(ship);
        EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Flashing, sprite);
    }
    co_yield Gng2D::Coroutine::Wait{7};
    {
        auto& sprite = reg.get<Gng2D::Sprite>(ship);
        EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Normal, sprite);
    }
}

