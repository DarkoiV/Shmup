#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/window.hpp"

void Gng2D::AssetRegistry::loadSprite(const std::string& name)
{
    if (globalSprites.contains(name)) return LOG::WARN("Sprite", name, "already loaded");
    if (auto* sprite = loadSpriteFile(name)) globalSprites[name] = sprite; 
}

SDL_Texture* Gng2D::AssetRegistry::loadSpriteFile(const std::string& name, const std::string& path)
{
    LOG::INFO("Loading sprite:", name);
    const std::string pathToSprite{path + name + ".png"};
    auto sprite = IMG_LoadTexture(renderer, pathToSprite.c_str());

    if (not sprite) LOG::ERROR("Failed to load sprite:", name, "SDL Error:", SDL_GetError());
    return sprite;
}

SDL_Texture* Gng2D::AssetRegistry::getSprite(const std::string& name) const
{
    if (not globalSprites.contains(name))
    {
        LOG::ERROR("No sprite:", name);
        return nullptr;
    }
    return globalSprites.at(name);
}

void Gng2D::AssetRegistry::freeAllSprites()
{
    LOG::INFO("Freeing loaded sprites");
    for (const auto& [_, texture] : globalSprites)
    {
        SDL_DestroyTexture(texture);
    }
}
