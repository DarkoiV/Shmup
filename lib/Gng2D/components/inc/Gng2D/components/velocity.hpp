#pragma once
#include "Gng2D/components/v2d.hpp"

namespace Gng2D
{
struct Velocity
{
    V2d     value;
    float   max;
    float   dragFactor;
};
}
