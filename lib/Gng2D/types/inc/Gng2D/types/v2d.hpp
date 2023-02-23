#pragma once
#include <cmath>

namespace Gng2D
{
struct V2d
{
    float x;
    float y;

constexpr static float distance(V2d first, V2d second)
{
    return std::sqrt(
            std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2));
}

constexpr static float sqrDistance(V2d first, V2d second)
{
    return  std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2);
}

constexpr V2d& operator+=(const V2d& lhs)
{
    x += lhs.x;
    y += lhs.y;
    return *this;
}
};

constexpr V2d operator+(const V2d& rhs, const V2d& lhs)
{
    return {rhs.x + lhs.x, rhs.y + lhs.y};
}

constexpr V2d operator-(const V2d& rhs, const V2d& lhs)
{
    return {rhs.x - lhs.x, rhs.y - lhs.y};
}
}