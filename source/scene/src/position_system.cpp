#include "Gng2D/scene/position_system.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/velocity.hpp"

using Gng2D::PositionSystem;

PositionSystem::PositionSystem(entt::registry& r)
    : reg(r)
    , parentPosObserver(reg, entt::collector.update<Position>().where<Children>())
{
    reg
        .on_construct<RelativePosition>()
        .connect<&PositionSystem::attachPositionToRelativePosition>();

    reg.ctx().emplace<PositionSystem&>(*this);
}

PositionSystem::~PositionSystem()
{
    reg
        .on_construct<RelativePosition>()
        .disconnect<&PositionSystem::attachPositionToRelativePosition>();
}

void PositionSystem::operator()()
{
    updatePosition();
    updateRelativePosition();
}


void PositionSystem::updatePosition()
{
    auto view = reg.view<Position, Velocity>();
    for (auto entity : view)
    {
        reg.patch<Position>(entity, [&](Position& pos)
        {
            auto& vel = view.get<Velocity>(entity);
            pos += vel;
        });
    }
}

void PositionSystem::updateRelativePosition()
{
    parentPosObserver.each([&](auto entity)
    {
        auto& children  = reg.get<Children>(entity).list;
        auto& parentPos = reg.get<Position>(entity);
        for (const auto child : children)
        {
            if (auto relativePos = reg.try_get<RelativePosition>(child))
            {
                reg.patch<Position>(child, [&](auto& pos)
                {
                    pos.x = relativePos->x + parentPos.x;
                    pos.y = relativePos->y + parentPos.y;
                });
            }
        }
    });
}

void PositionSystem::attachPositionToRelativePosition(entt::registry& reg, entt::entity entity)
{
    auto parent     = reg.get<Parent>(entity).id;
    auto& parentPos = reg.get<Position>(parent);
    auto& relPos    = reg.get<RelativePosition>(entity);
    reg.emplace<Position>(entity, parentPos.x + relPos.x, parentPos.y + relPos.y);
}

