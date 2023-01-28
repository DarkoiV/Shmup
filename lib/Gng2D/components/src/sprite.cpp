#include "Gng2D/components/sprite.hpp"
#include "Gng2D/internal/asset_registry.hpp"

Gng2D::Sprite::Sprite(const std::string& name, SDL_Rect src)
    : texture(AssetRegistry::get().getSprite(name))
    , srcRect(src)
{
}
