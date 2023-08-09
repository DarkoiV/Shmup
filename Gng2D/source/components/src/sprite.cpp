#include "Gng2D/components/sprite.hpp"
#include "Gng2D/core/asset_registry.hpp"

Gng2D::Sprite::Sprite(const std::string& name, SDL_Rect src)
    : texture(AssetRegistry().getSprite(name))
    , srcRect(src)
{
}

Gng2D::Sprite::Sprite(const std::string& name)
    : texture(AssetRegistry().getSprite(name))
{
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &srcRect.w, &srcRect.h);
}
    
Gng2D::Sprite::Sprite(SDL_Texture* texture)
    : texture(texture)
{
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &srcRect.w, &srcRect.h);
}

