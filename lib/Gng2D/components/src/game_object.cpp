#include "Gng2D/components/game_object.hpp"

Gng2D::GameObject::GameObject(entt::registry& reg)
    : registry(reg)
    , id(registry.create())
{
}

Gng2D::GameObject::~GameObject()
{
    registry.destroy(id);
}

entt::entity Gng2D::GameObject::getId() const
{
    return id;
}
