#include "animations.hpp"
#include "Gng2D/components/roation.hpp"

void emplaceAnimation(AnimationFunction af, entt::registry& reg, entt::entity e)
{
    reg.emplace_or_replace<Gng2D::Animation>(e, af, reg, e);
}

Gng2D::Coroutine flashShip(entt::registry& reg, entt::entity ship)
{
    {
        reg.patch<Gng2D::Sprite>(ship, [](auto& sprite)
        {
            EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Flashing, sprite);
        });
    }
    co_yield Gng2D::Coroutine::Wait{7};
    {
        reg.patch<Gng2D::Sprite>(ship, [](auto& sprite)
        {
            EnemySpriteSheet::setVFrame(EnemySpriteSheet::VFrame::Normal, sprite);
        });
    }
}

static void selectPickupFrame(entt::registry& reg, entt::entity pickup, int frame)
{
    reg.patch<Gng2D::Sprite>(pickup, [frame](auto& sprite)
    {
        sprite.srcRect.x = frame * sprite.srcRect.w;
    });
}

Gng2D::Coroutine rotatePickup(entt::registry& reg, entt::entity pickup)
{
    while (true)
    {
        selectPickupFrame(reg, pickup, 0);
        co_yield Gng2D::Coroutine::Wait{14};
        selectPickupFrame(reg, pickup, 1);
        co_yield Gng2D::Coroutine::Wait{7};
        selectPickupFrame(reg, pickup, 2);
        co_yield Gng2D::Coroutine::Wait{7};
        selectPickupFrame(reg, pickup, 3);
        co_yield Gng2D::Coroutine::Wait{7};
        selectPickupFrame(reg, pickup, 2);
        co_yield Gng2D::Coroutine::Wait{7};
        selectPickupFrame(reg, pickup, 1);
        co_yield Gng2D::Coroutine::Wait{7};
    }
}

Gng2D::Coroutine laserShoot(entt::registry& reg, entt::entity laser)
{
    co_yield Gng2D::Coroutine::Wait{1};
    reg.template patch<Gng2D::Sprite>(laser, [](auto& sprite)
    {
        sprite.srcRect.y = sprite.srcRect.h * 1;
    });

    co_yield Gng2D::Coroutine::Wait{1};
    reg.template patch<Gng2D::Sprite>(laser, [](auto& sprite)
    {
        sprite.srcRect.y = sprite.srcRect.h * 2;
    });

    co_yield Gng2D::Coroutine::Wait{1};
    reg.template patch<Gng2D::Sprite>(laser, [](auto& sprite)
    {
        sprite.srcRect.y = sprite.srcRect.h * 3;
    });
}

Gng2D::Coroutine rotateChargeMarker(entt::registry& reg, entt::entity marker)
{
    while (true) 
    {
        reg.patch<Gng2D::Rotation>(marker, [](auto& rotation)
        {
            rotation.angle += 10;
            if (rotation.angle == 360) rotation.angle = 0;
        });
        co_yield Gng2D::Coroutine::Wait{1};
    }
}

