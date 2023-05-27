#include "systems/entity_cleaner.hpp"
#include "Gng2D/core/settings.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "components/destroy.hpp"

EntityCleaner::EntityCleaner(entt::registry& r)
    : reg(r)
{
}

void EntityCleaner::operator()()
{
    outOfScreenCleaner();
    destroyedCleaner();
}

void EntityCleaner::outOfScreenCleaner()
{
    constexpr int margin = 10;
    const auto maxX = Gng2D::SCREEN_WIDTH   + margin;
    const auto maxY = Gng2D::SCREEN_HEIGHT  + margin;

    for (auto&& [entity, pos] : reg.view<Gng2D::Position>().each())
    {
        bool outside 
            =   pos.x < -margin or pos.y < -margin
            or  pos.x > maxX    or pos.y > maxY;
        if (outside) reg.destroy(entity);
    }
}

void EntityCleaner::destroyedCleaner()
{
    for (auto [entity, destroy] : reg.view<Destroy>().each())
    {
        if (destroy.remainingTicks == 0) 
        {
            if (destroy.effect == Destroy::Effect::spawnRedX) spawnRedX(entity);
            reg.destroy(entity); 
        }
        else destroy.remainingTicks--;
    }
}

void EntityCleaner::spawnRedX(entt::entity entity)
{
    auto& pos = reg.get<Gng2D::Position>(entity);
    auto redX = reg.create();
    auto& sprite = reg.emplace<Gng2D::Sprite>(redX, "red_x");
    sprite.opacity = 200;
    reg.emplace<Gng2D::Position>(redX, pos);
    reg.emplace<Destroy>(redX, Destroy::Effect::noEffect, 20u);
}

