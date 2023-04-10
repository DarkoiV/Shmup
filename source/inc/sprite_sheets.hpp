#pragma once
#include "Gng2D/components/sprite.hpp"

struct PlayerSpriteSheet
{
    static constexpr unsigned hFrames = 3;
    static constexpr unsigned vFrames = 1;

    enum class HFrame
    {
        Forward,
        Right,
        Left
    };

    static void divideSprite(Gng2D::Sprite& s)
    {
        s.srcRect.w /= hFrames;
        s.srcRect.h /= vFrames;
    }

    static void setHFrame(HFrame f, Gng2D::Sprite& s)
    {
        int horizontalFrame = static_cast<int>(f) % hFrames;
        s.srcRect.x = horizontalFrame * s.srcRect.w;
    }
};

struct EnemySpriteSheet
{
    static constexpr unsigned hFrames = 3;
    static constexpr unsigned vFrames = 2;

    enum class HFrame
    {
        Forward,
        Right,
        Left
    };

    enum class VFrame 
    {
        Normal,
        Flashing
    };

    static void divideSprite(Gng2D::Sprite& s)
    {
        s.srcRect.w /= hFrames;
        s.srcRect.h /= vFrames;
    }

    static void setHFrame(HFrame f, Gng2D::Sprite& s)
    {
        int horizontalFrame = static_cast<int>(f) % hFrames;
        s.srcRect.x = horizontalFrame * s.srcRect.w;
    }

    static void setVFrame(VFrame f, Gng2D::Sprite& s)
    {
        int verticalFrame = static_cast<int>(f) % vFrames;
        s.srcRect.y = verticalFrame * s.srcRect.h;
    }
};

