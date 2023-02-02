#pragma once
#include <map>
#include <memory>
#include <string>

struct SDL_Texture;

namespace Gng2D
{
struct AssetRegistry
{
    void loadSprite(const std::string& name);
    auto getSprite(const std::string& name) const -> SDL_Texture*;
    void freeAllSprites();

private:
    inline static std::map<std::string, SDL_Texture*> loadedSprites;
};
}
