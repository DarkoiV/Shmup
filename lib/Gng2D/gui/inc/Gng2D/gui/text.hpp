#pragma once
#include <string>
#include "Gng2D/types/font.hpp"
#include "Gng2D/gui/element.hpp"

namespace Gng2D::gui
{
struct Text : Element
{
    Text(const std::string& font, const std::string& str);

    void    render(SDL_Renderer*) const         override;
    void    setOriginPoint(int x, int y)        override;
    void    setPosition(Align, int x, int y)    override;
    void    setScale(unsigned)                  override;
    void    setOpacity(uint8_t)                 override;
    int     width()     const                   override;
    int     height()    const                   override;

    void    changeFont(const std::string& font);

private:
    Font            font;
    std::string     str;
};
}
