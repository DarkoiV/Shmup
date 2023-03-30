#pragma once
#include <string>
#include "Gng2D/types/font.hpp"
#include "Gng2D/gui/element.hpp"

namespace Gng2D::gui
{
struct Text : Element
{
    Text(const std::string& font, const std::string& str);

    void    render(SDL_Renderer*)   const override;
    int     width()                 const override;
    int     height()                const override;

    void    changeFont(const std::string& font);
    void    setColorMod(uint8_t r, uint8_t g, uint8_t b);

private:
    Font            font;
    std::string     str;

    uint8_t     redMod{255};
    uint8_t     greenMod{255};
    uint8_t     blueMod{255};
};
}
