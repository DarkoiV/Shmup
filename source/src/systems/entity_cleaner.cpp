#include "systems/entity_cleaner.hpp"
#include "Gng2D/core/settings.hpp"
#include "Gng2D/components/position.hpp"
#include "components/timed_existence.hpp"

EntityCleaner::EntityCleaner(Gng2D::Scene& s)
    : scene(s)
{
}

void EntityCleaner::operator()()
{
    outOfScreenCleaner();
    timedExistence();
}

void EntityCleaner::outOfScreenCleaner()
{
    constexpr int margin = 10;
    const auto maxX = Gng2D::SCREEN_WIDTH   + margin;
    const auto maxY = Gng2D::SCREEN_HEIGHT  + margin;

    for (const auto& [e, pos] : scene.view<Gng2D::Position>())
    {
        bool outside 
            =   pos.x < -margin or pos.y < -margin
            or  pos.x > maxX    or pos.y > maxY;
        if (outside) scene.destroyEntity(e);
    }
}

void EntityCleaner::timedExistence()
{
    for (const auto& [e, te] : scene.view<TimedExistence>())
    {
        te.remainingTicks--;
        if (te.remainingTicks == 0) scene.destroyEntity(e);
    }
}

