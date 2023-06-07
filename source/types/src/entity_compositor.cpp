#include "Gng2D/types/entity_compositor.hpp"
#include "Gng2D/components/relationship.hpp"

using Gng2D::EntityCompositor;

EntityCompositor& EntityCompositor::withParent(entt::entity parent)
{
    reg.emplace<Parent>(entity, parent);
    return *this;
}
