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

void Gng2D::AssetRegistry::loadBMFont(const std::string& name, int charW, int charH)
{
    if (globalFonts.contains(name)) return LOG::WARN("Font", name, "already loaded");
    auto* fontSprite = loadSpriteFile(name, "data/fonts/");
    if (not fontSprite) return;

    int width;
    SDL_QueryTexture(fontSprite, nullptr, nullptr, &width, nullptr);
    int charsPerRow = width / charW;

    globalFonts.emplace(name, Font(fontSprite, charW, charH, charsPerRow));
    globalSprites["fonts/" + name] = fontSprite;
}

SDL_Texture* Gng2D::AssetRegistry::loadSpriteFile(const std::string& name, const std::string& path)
{
    LOG::INFO("Loading:", name);
    const std::string pathToSprite{path + name + ".png"};
    auto sprite = IMG_LoadTexture(renderer, pathToSprite.c_str());

    if (not sprite) LOG::ERROR("Failed to load:", name, "SDL Error:", SDL_GetError());
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

Gng2D::Font Gng2D::AssetRegistry::getFont(const std::string& name) const
{
    if (not globalFonts.contains(name))
    {
        LOG::ERROR("No font:", name);
        return Font(nullptr, 0, 0, 0);
    }
    return globalFonts.at(name);
}

void Gng2D::AssetRegistry::freeAllSprites()
{
    LOG::INFO("Freeing loaded sprites");
    for (const auto& [_, texture] : globalSprites)
    {
        SDL_DestroyTexture(texture);
    }
}
