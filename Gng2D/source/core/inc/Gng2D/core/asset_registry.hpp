#pragma once
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <optional>
#include <SDL2/SDL.h>
#include "Gng2D/types/font.hpp"
#include "Gng2D/components/selection_list.hpp"

struct SDL_Texture;

namespace Gng2D
{
struct Application;
struct AssetRegistry
{
    void            loadSprite(const std::string& name);
    void            loadBMFont(const std::string& name, int charW, int charH);
    SDL_Texture*    getSprite(const std::string& name)  const;
    Font            getFont(const std::string& name)    const;

    void                setDefaultFont(const std::string& name);
    void                setDefaultBoxTiles(const std::string& name);
    void                setDefaultOnHighlightFunc(SelectionList::ModFunc);
    void                setDefaultOnStopHighlightFunc(SelectionList::ModFunc);

    std::optional<Font>     getDefaultFont()                const;
    SDL_Texture*            getDefaultBoxTiles()            const;
    SelectionList::ModFunc  getDefaultOnHighlightFunc()     const;
    SelectionList::ModFunc  getDefaultOnStopHighlightFunc() const;


    struct RenderToTexture
    {
        using Commands = std::function<void(SDL_Renderer*)>;
        RenderToTexture(int width, int height, Commands);
        ~RenderToTexture();

        SDL_Texture*        getTexture();
        void                saveTexture(const std::string& name);

    private:
        bool            transferredOwnership{false};
        SDL_Texture*    target{nullptr};
    };

private:
    SDL_Texture*    loadSpriteFile(const std::string& name, 
                                   const std::string& path = "data/sprites/");

    inline static std::map<std::string, SDL_Texture*>   globalSprites;
    inline static std::map<std::string, Font>           globalFonts;

    // Defaults
    inline static std::optional<Font>           defaultFont{std::nullopt};
    inline static SDL_Texture*                  defaultBoxTiles{nullptr};
    inline static SelectionList::ModFunc        defaultOnHighlight;
    inline static SelectionList::ModFunc        defaultOnStopHighlight;

    /// ONLY FOR APPLICATION ///
    friend struct   Application;
    void            freeAllSprites();
    inline static   SDL_Renderer* renderer;
};
}

