#pragma once
#include <cmath>
#include <numbers>

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

    constexpr static V2d rot(float degrees, float length)
    {
        float rad = degrees * (std::numbers::pi / 180);
        float x = std::cos(rad) * length;
        float y = std::sin(rad) * length;
        return V2d{x, y};
    }

    constexpr static V2d normalize(V2d vec)
    {
        float len = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
        return {vec.x / len, vec.y / len};
    }

    constexpr V2d& operator+=(const V2d& lhs)
    {
        x += lhs.x;
        y += lhs.y;
        return *this;
    }
};

constexpr V2d operator*(const float rhs, const V2d& lhs)
{
    return {rhs * lhs.x, rhs * lhs.y};
}

constexpr V2d operator+(const V2d& rhs, const V2d& lhs)
{
    return {rhs.x + lhs.x, rhs.y + lhs.y};
}

constexpr V2d operator-(const V2d& rhs, const V2d& lhs)
{
    return {rhs.x - lhs.x, rhs.y - lhs.y};
}
}
