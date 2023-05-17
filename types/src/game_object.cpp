#include "Gng2D/types/game_object.hpp"
#include "Gng2D/types/scene.hpp"

using Gng2D::GameObject;

GameObject::GameObject(Scene& s)
    : scene(s)
    , registry(s.registry)
    , id(registry.create())
{
}

GameObject::GameObject(Scene& s, entt::entity id)
    : scene(s)
    , registry(s.registry)
    , id(id)
{
}

entt::entity GameObject::getId() const
{
    return id;
}

void GameObject::addName(const std::string& name)
{
    if (scene.namedEntities.contains(name)) LOG::ERROR(name, "has been already registered!");
    else
    {
        scene.namedEntities[name] = id;
    }
}

bool GameObject::isValid() const 
{
    return registry.valid(id);
}

