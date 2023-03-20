#include "Gng2D/gui/icon.hpp"
#include "Gng2D/core/asset_registry.hpp"

using Gng2D::gui::Icon;
using namespace Gng2D;

Icon::Icon(const std::string& spriteName, SDL_Rect src)
    : texture(AssetRegistry().getSprite(spriteName))
    , srcRect(src)
{
}

void Icon::render(SDL_Renderer* r) const
{
    SDL_Rect dstRect;

    dstRect.x = originPointX;
    dstRect.y = originPointY;
    dstRect.w = srcRect.w * scale;
    dstRect.h = srcRect.h * scale;

    SDL_SetTextureAlphaMod(texture, opacity);
    SDL_RenderCopy(r, texture, &srcRect, &dstRect);
}

int Icon::width() const
{
    return srcRect.w * scale;
}

int Icon::height() const 
{
    return srcRect.h * scale;
}
