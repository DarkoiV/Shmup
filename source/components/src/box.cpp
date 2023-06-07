#include "Gng2D/components/box.hpp"
#include "Gng2D/core/asset_registry.hpp"

using Gng2D::Box;

Box::Box(const std::string& sprite, unsigned capWidth, unsigned capHeight, unsigned margin)
    : tilesSprite(AssetRegistry().getSprite(sprite))
    , capacityWidth(capWidth)
    , capacityHeight(capHeight)
    , capacityMargin(margin)
{
    generateNewTexture();
}

SDL_Texture* Box::getSprite() const 
{
    return boxSprite.get();
}

void Box::setCapacity(unsigned width, unsigned height, unsigned margin)
{
    capacityWidth   = width;
    capacityHeight  = height;
    capacityMargin  = margin;
}

void Box::generateNewTexture()
{
    int tileWidth;
    int tileHeight;
    SDL_QueryTexture(tilesSprite, nullptr, nullptr, &tileWidth, &tileHeight);
    tileWidth /= 3; 
    tileHeight /= 3;
    
    int boxWidth = capacityWidth + 2*capacityMargin + 2*tileWidth;
    int boxHeight = capacityHeight + 2*capacityMargin + 2*tileHeight;
    auto newSprite = AssetRegistry::RenderToTexture(boxWidth, boxHeight, [&](SDL_Renderer* r)
    {    
        // TOP LEFT
        SDL_Rect dstRect{0, 
                         0, 
                         static_cast<int>(tileWidth),
                         static_cast<int>(tileHeight)};
        SDL_Rect srcRect{0, 0, tileWidth, tileHeight};

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // TOP MIDDLE
        dstRect.x += tileWidth;
        dstRect.w  = capacityMargin + capacityWidth;
        srcRect.x  = tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // TOP RIGHT
        dstRect.x += capacityMargin + capacityWidth;
        dstRect.w  = tileWidth;
        srcRect.x  = 2*tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // CENTER LEFT
        dstRect.x  = 0;
        dstRect.y += tileHeight;
        dstRect.h  = capacityMargin + capacityHeight;
        srcRect.x  = 0;
        srcRect.y  = tileHeight;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // CENTER MIDDLE
        dstRect.x += tileWidth;
        dstRect.w  = capacityMargin + capacityWidth;
        srcRect.x  = tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // CENTER RIGHT
        dstRect.x += capacityMargin + capacityWidth;
        dstRect.w  = tileWidth;
        srcRect.x  = 2*tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // BOTTOM LEFT
        dstRect.x  = 0;
        dstRect.y += capacityMargin + capacityHeight;
        dstRect.h  = tileHeight;
        srcRect.x  = 0;
        srcRect.y  = 2*tileHeight;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // BOTOM MIDDLE
        dstRect.x += tileWidth;
        dstRect.w  = capacityMargin + capacityWidth;
        srcRect.x  = tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);

        // BOTTOM RIGHT
        dstRect.x += capacityMargin + capacityWidth;
        dstRect.w  = tileWidth;
        srcRect.x  = 2*tileWidth;

        SDL_RenderCopy(r, tilesSprite, &srcRect, &dstRect);
    }).getTexture();

    boxSprite = OwnedTexture(newSprite, &SDL_DestroyTexture);
}

