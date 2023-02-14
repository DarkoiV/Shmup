#pragma once
#include <map>
#include <memory>
#include <string>
#include "SDL2/SDL.h"

struct SDL_Texture;

namespace Gng2D
{
struct Application;
struct AssetRegistry
{
    void            loadSprite(const std::string& name);
    SDL_Texture*    getSprite(const std::string& name) const;
    void            freeAllSprites();

private:
    inline static std::map<std::string, SDL_Texture*> loadedSprites;

    friend struct Application;
    inline static SDL_Renderer* renderer;
};
}
