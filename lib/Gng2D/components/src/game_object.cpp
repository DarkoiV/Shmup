#include "Gng2D/components/game_object.hpp"
#include "Gng2D/components/scene.hpp"

Gng2D::GameObject::GameObject(Gng2D::Scene& s)
    : registry(s.registry)
    , id(registry.create())
{
}

entt::entity Gng2D::GameObject::getId() const
{
    return id;
}
