#pragma once
#include "entt/entity/registry.hpp"

namespace Gng2D
{
struct GameObject
{
    GameObject(entt::registry&);
    virtual ~GameObject();

protected:
    entt::registry&     registry;
    const entt::entity  id;
};
}
