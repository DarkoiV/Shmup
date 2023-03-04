#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Gng2D
{
struct Sprite
{
    Sprite(const std::string& spriteName, SDL_Rect src, unsigned layer = 0, float scale = 1.0f);
    Sprite(const std::string& spriteName, unsigned layer = 0, float scale = 1.0f);

    SDL_Texture*    texture;
    SDL_Rect        srcRect;
    unsigned        layer;
    float           scale;
};
}
