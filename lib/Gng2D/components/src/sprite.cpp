#include "Gng2D/components/sprite.hpp"
#include "Gng2D/core/asset_registry.hpp"

Gng2D::Sprite::Sprite(const std::string& name, SDL_Rect src, unsigned layer, float scale)
    : texture(AssetRegistry().getSprite(name))
    , srcRect(src)
    , layer(layer)
    , scale(scale)
{
}

Gng2D::Sprite::Sprite(const std::string& name, unsigned layer, float scale)
    : texture(AssetRegistry().getSprite(name))
    , layer(layer)
    , scale(scale)
{
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &srcRect.w, &srcRect.h);
}
