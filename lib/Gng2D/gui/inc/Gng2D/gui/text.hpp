#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Gng2D/types/font.hpp"

namespace Gng2D::gui
{
struct Text
{
    Text(const std::string& font, const std::string& str);
    void    render(SDL_Renderer*, int originPointX, int originPointY) const;

    void    setScale(unsigned);
    void    changeFont(const std::string& font);
    int     width()     const;
    int     height()    const;

private:
    unsigned        scale{1};
    Font            font;
    std::string     str;
};
}
