#pragma once
#include <type_traits>

namespace Gng2D
{
struct CircleCollider
{
    float radius;
};

template<typename C>
concept CircleColliderType = std::is_base_of<CircleCollider, C>::value;
}

