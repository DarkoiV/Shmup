#pragma once
#include <entt/entt.hpp>
#include <vector>

namespace Gng2D
{
struct Child 
{
    Child(entt::entity p)
        : parent(p) {}
    entt::entity parent;
};

struct Parent 
{
    std::vector<entt::entity> children;
};
}

