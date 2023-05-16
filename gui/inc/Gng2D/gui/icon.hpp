#pragma once
#include <string>
#include "Gng2D/gui/element.hpp"

namespace Gng2D::gui
{
struct Icon : Element
{
    Icon(const std::string& sprite);
    Icon(const std::string& sprite, SDL_Rect srcRect);

    void    render(SDL_Renderer*)   const override;
    int     width()                 const override;
    int     height()                const override;

private:
    SDL_Texture*    texture;
    SDL_Rect        srcRect;
};
}

