#include "Gng2D/components/game_object.hpp"
#include "Gng2D/components/scene.hpp"

Gng2D::GameObject::GameObject(Gng2D::Scene& s)
    : registry(s.registry)
    , id(registry.create())
{
}

Gng2D::GameObject::GameObject(Gng2D::Scene& s, entt::entity id)
    : registry(s.registry)
    , id(id)
{
}

entt::entity Gng2D::GameObject::getId() const
{
    return id;
}
