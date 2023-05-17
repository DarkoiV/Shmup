#include "Gng2D/components/sprite.hpp"
#include "Gng2D/core/asset_registry.hpp"

Gng2D::Sprite::Sprite(const std::string& name, SDL_Rect src, float scale)
    : texture(AssetRegistry().getSprite(name))
    , srcRect(src)
    , scale(scale)
{
}

Gng2D::Sprite::Sprite(const std::string& name, float scale)
    : texture(AssetRegistry().getSprite(name))
    , scale(scale)
{
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &srcRect.w, &srcRect.h);
}

Gng2D::Sprite::Sprite(const TextSprite& text)
    : texture(text.getSprite())
    , scale(text.getScale())
{
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &srcRect.w, &srcRect.h);
}

