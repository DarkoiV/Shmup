#include "Gng2D/types/game_object.hpp"
#include "Gng2D/types/scene.hpp"

Gng2D::GameObject::GameObject(Gng2D::Scene& s)
    : scene(s)
    , registry(s.registry)
    , id(registry.create())
{
}

Gng2D::GameObject::GameObject(Gng2D::Scene& s, entt::entity id)
    : scene(s)
    , registry(s.registry)
    , id(id)
{
}

entt::entity Gng2D::GameObject::getId() const
{
    return id;
}

bool Gng2D::GameObject::isValid() const 
{
    return registry.valid(id);
}

