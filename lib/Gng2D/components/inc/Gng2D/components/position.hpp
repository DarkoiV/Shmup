#pragma once
#include <cstdint>
#include "Gng2D/types/v2d.hpp"
#include "Gng2D/core/settings.hpp"

namespace Gng2D
{
struct Position
{
    Position(V2d pos)
        : oldFramePos(pos)
        , newFramePos(pos){};

    Position(float x, float y)
        : oldFramePos(V2d{x, y})
        , newFramePos(V2d{x, y}){};

    constexpr Position& operator+=(const V2d rhs)
    {
        oldFramePos = newFramePos;
        newFramePos.x += rhs.x;
        newFramePos.y += rhs.y;
        return *this;
    }

    constexpr Position& operator-=(const V2d rhs)
    {
        oldFramePos = newFramePos;
        newFramePos.x -= rhs.x;
        newFramePos.y -= rhs.y;
        return *this;
    }

    // interpolates position between previous and next frame
    V2d operator()(uint32_t msLag) const
    {
        float oldFrameBias = static_cast<float>(LOGIC_TICK - msLag) / static_cast<float>(LOGIC_TICK);
        float newFrameBias = 1.0f - oldFrameBias;
        return V2d{oldFramePos.x * oldFrameBias + newFramePos.x * newFrameBias,
                   oldFramePos.y * oldFrameBias + newFramePos.y * newFrameBias};
    }

    void bound(const V2d min, const V2d max)
    {
        if (newFramePos.x < min.x) newFramePos.x = min.x;
        if (newFramePos.y < min.y) newFramePos.y = min.y;
        if (newFramePos.x > max.x) newFramePos.x = max.x;
        if (newFramePos.y > max.y) newFramePos.y = max.y;
    };

private:
    V2d oldFramePos;
    V2d newFramePos;
};
}

