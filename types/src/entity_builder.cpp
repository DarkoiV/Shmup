#include "Gng2D/types/entity_builder.hpp"
#include "Gng2D/components/relationship.hpp"

using Gng2D::EntityBuilder;

EntityBuilder& EntityBuilder::withParent(entt::entity parent)
{
    reg.emplace<Child>(entity, parent);
    return *this;
}
