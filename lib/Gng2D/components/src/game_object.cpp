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

auto Gng2D::GameObject::getId() const -> entt::entity
{
    return id;
}
