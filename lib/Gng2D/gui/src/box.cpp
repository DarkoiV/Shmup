#include "Gng2D/gui/box.hpp"
#include "Gng2D/core/asset_registry.hpp"

using Gng2D::gui::Box;
using namespace Gng2D;

Box::Box(const std::string& boxSprite)
    : texture(AssetRegistry().getSprite(boxSprite))
{
    SDL_QueryTexture(texture, nullptr, nullptr, &boxTileWidth, &boxTileHeight);
    boxTileWidth    /= 3;
    boxTileHeight   /= 3;
}

void Box::render(SDL_Renderer* r) const 
{
    // TOP LEFT
    SDL_Rect dstRect{originPointX, 
                     originPointY, 
                     static_cast<int>(boxTileWidth * scale),
                     static_cast<int>(boxTileHeight * scale)};
    SDL_Rect srcRect{0, 0, boxTileWidth, boxTileHeight};

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // TOP MIDDLE
    dstRect.x += boxTileWidth * scale;
    dstRect.w  = capacityMargin + capacityWidth;
    srcRect.x  = boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // TOP RIGHT
    dstRect.x += capacityMargin + capacityWidth;
    dstRect.w  = boxTileWidth * scale;
    srcRect.x  = 2*boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // CENTER LEFT
    dstRect.x  = originPointX;
    dstRect.y += boxTileHeight;
    dstRect.h  = capacityMargin + capacityHeight;
    srcRect.x  = 0;
    srcRect.y  = boxTileHeight;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // CENTER MIDDLE
    dstRect.x += boxTileWidth * scale;
    dstRect.w  = capacityMargin + capacityWidth;
    srcRect.x  = boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // CENTER RIGHT
    dstRect.x += capacityMargin + capacityWidth;
    dstRect.w  = boxTileWidth * scale;
    srcRect.x  = 2*boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // BOTTOM LEFT
    dstRect.x  = originPointX;
    dstRect.y += capacityMargin + capacityHeight;
    dstRect.h  = boxTileHeight * scale;
    srcRect.x  = 0;
    srcRect.y  = 2*boxTileHeight;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // BOTOM MIDDLE
    dstRect.x += boxTileWidth * scale;
    dstRect.w  = capacityMargin + capacityWidth;
    srcRect.x  = boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);

    // BOTTOM RIGHT
    dstRect.x += capacityMargin + capacityWidth;
    dstRect.w  = boxTileWidth * scale;
    srcRect.x  = 2*boxTileWidth;

    SDL_RenderCopy(r, texture, &srcRect, &dstRect);
}

int Box::width() const
{
    return (capacityWidth + capacityMargin + (boxTileWidth*2)) * scale;
}

int Box::height() const 
{
    return (capacityHeight + capacityMargin + (boxTileHeight*2)) * scale;
}

void Box::setCapacity(int w, int h, int m)
{
    capacityWidth   = w;
    capacityHeight  = h;
    capacityMargin  = m;
}

std::pair<int, int> Box::innerOrgin() const 
{
    return {originPointX + (boxTileWidth  * scale) + capacityMargin,
            originPointY + (boxTileHeight * scale) + capacityMargin};
}

