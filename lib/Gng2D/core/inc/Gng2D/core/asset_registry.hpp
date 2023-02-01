#pragma once
#include <map>
#include <memory>
#include <string>

struct SDL_Texture;

namespace Gng2D
{
struct AssetRegistry
{
    static void loadSprite(const std::string& name);
    static auto getSprite(const std::string& name) -> SDL_Texture*;
    static void freeAllSprites();

private:
    inline static std::map<std::string, SDL_Texture*> loadedSprites;
};
}
