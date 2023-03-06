#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "Gng2D/types/font.hpp"

namespace Gng2D::gui
{
struct Text
{
    enum class Align 
    {
        Center,
    };

    Text(const std::string& font, const std::string& str);
    void    render(SDL_Renderer*) const;

    void    setOriginPoint(int x, int y);
    void    setPosition(Align, int x, int y);
    void    setScale(unsigned);
    void    setOpacity(uint8_t);
    void    changeFont(const std::string& font);
    int     width()     const;
    int     height()    const;

private:
    int             originPointX{0};
    int             originPointY{0};
    unsigned        scale{1};
    uint8_t         opacity{255};
    Font            font;
    std::string     str;
};
}
