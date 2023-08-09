#pragma once
#include <cstdint>
#include <compare>

namespace Gng2D
{
struct Layer
{
    uint8_t main{0};
    uint8_t sub{0};

    auto operator<=>(const Layer&) const = default;
};
}

