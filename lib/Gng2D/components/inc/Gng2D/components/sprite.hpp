#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace Gng2D
{
struct Sprite
{
    Sprite(const std::string& spriteName, SDL_Rect src);

    SDL_Texture*    texture;
    SDL_Rect        srcRect;
};
}
