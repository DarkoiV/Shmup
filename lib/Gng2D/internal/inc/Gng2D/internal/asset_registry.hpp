#pragma once
#include <map>
#include <memory>
#include <string>

struct SDL_Texture;

namespace Gng2D
{
struct AssetRegistry
{
    static void init();
    static void destroy();
    static auto get()       -> AssetRegistry&;

    void loadSprite(const std::string& name);
    auto getSprite(const std::string& name) const -> SDL_Texture*;

private:
    inline static AssetRegistry*        instance;

    AssetRegistry()     = default;
    ~AssetRegistry();

    std::map<std::string, SDL_Texture*> loadedSprites;
};
}
