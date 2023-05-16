#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Gng2D/components/text.hpp"

namespace Gng2D
{
struct Sprite
{
    Sprite(const std::string& spriteName, SDL_Rect src, float scale = 1.0f);
    Sprite(const std::string& spriteName, float scale = 1.0f);
    Sprite(const Text&, float scale = 1.0f);

    SDL_Texture*    texture;
    SDL_Rect        srcRect;
    float           scale;
    uint8_t         opacity{255};
};
}
