#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include "Gng2D/types/v2d.hpp"

namespace Gng2D
{
struct Box
{
    Box(const std::string& sprite, 
        unsigned capWidth, 
        unsigned capHeight, 
        unsigned margin = 0);

    SDL_Texture*    getSprite() const;
    void            setCapacity(unsigned width, unsigned height, unsigned margin = 0);

private:
    using OwnedTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
    void generateNewTexture();

    OwnedTexture    boxSprite{nullptr, &SDL_DestroyTexture};
    SDL_Texture*    tilesSprite;
    unsigned        capacityWidth;
    unsigned        capacityHeight;
    unsigned        capacityMargin;
};
}

