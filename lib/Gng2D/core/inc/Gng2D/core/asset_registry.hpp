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
    SDL_Texture*    getSprite(const std::string& name) const;
    void            loadSprite(const std::string& name);

private:
    SDL_Texture*    loadSpriteFile(const std::string& name, 
                                   const std::string& path = "data/sprites/");

    inline static std::map<std::string, SDL_Texture*> globalSprites;

    /// ONLY FOR APPLICATION ///
    friend struct Application;
    void                        freeAllSprites();
    inline static SDL_Renderer* renderer;
};
}
