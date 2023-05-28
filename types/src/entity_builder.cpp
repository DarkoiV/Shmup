#include "Gng2D/types/entity_builder.hpp"
#include "Gng2D/components/relationship.hpp"

using Gng2D::EntityBuilder;

EntityBuilder& EntityBuilder::withChild(entt::entity child)
{
    reg.emplace<Child>(child, entity);
    return *this;
}
