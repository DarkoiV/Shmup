#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Gng2D/types/v2d.hpp"

namespace Gng2D
{
struct Sprite
{
    Sprite(const std::string& spriteName, SDL_Rect src);
    Sprite(const std::string& spriteName);
    Sprite(SDL_Texture*);

    SDL_Texture*    texture;
    SDL_Rect        srcRect;
};

struct SpriteStretch : V2d
{
};

struct SpriteOpacity 
{
    uint8_t value;
};

}
