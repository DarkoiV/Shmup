#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Gng2D/internal/asset_registry.hpp"
#include "Gng2D/internal/window.hpp"
#include "Gng2D/core/log.hpp"

void Gng2D::AssetRegistry::init()
{
    if (not Gng2D::Window::renderer()) LOG::FATAL("Window renderer needs to exist before asset registry");

    if (not instance) instance = new AssetRegistry;
    else LOG::WARN("Asset registry already exists");

    // TMP
    instance->loadSprite("data/Clojure.png");
}

void Gng2D::AssetRegistry::destroy()
{
    if (instance) 
    {
        delete instance;
        instance = nullptr;
    }
}

auto Gng2D::AssetRegistry::get() -> AssetRegistry&
{
    if (not instance) LOG::FATAL("Cannot get asset registry");
    return *instance;
}

void Gng2D::AssetRegistry::loadSprite(const std::string& name)
{
    auto renderer = Gng2D::Window::renderer();
    auto sprite = IMG_LoadTexture(renderer, name.c_str());

    if (not sprite) return LOG::ERROR("Failed to load sprite:", name, SDL_GetError());
    if (loadedTextures.contains(name)) return LOG::WARN("Sprite", name, "already loaded");

    loadedTextures[name] = sprite;
}

auto Gng2D::AssetRegistry::getSprite(const std::string& name) -> SDL_Texture*
{
    if (not loadedTextures.contains(name))
    {
        LOG::ERROR("No sprite:", name);
        return nullptr;
    }
    return loadedTextures.at(name);
}

Gng2D::AssetRegistry::~AssetRegistry()
{
    for (const auto& [_, texture] : loadedTextures)
    {
        SDL_DestroyTexture(texture);
    }
}
