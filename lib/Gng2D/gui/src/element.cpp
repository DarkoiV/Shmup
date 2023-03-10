#include "Gng2D/gui/element.hpp"
#include "Gng2D/core/settings.hpp"

using Gng2D::gui::Element;

void Element::setScale(unsigned s)
{
    scale = s;
}

void Element::setOpacity(uint8_t o)
{
    opacity = o;
}

void Element::setOriginPoint(int x, int y)
{
    originPointX = x;
    originPointY = y;
}

void Element::setPosition(Align a, int x, int y)
{
    if (a == Align::Center)
    {
        x = (SCREEN_WIDTH  / 2) - (width()  / 2) + x;
        y = (SCREEN_HEIGHT / 2) - (height() / 2) + y;
    }

    setOriginPoint(x, y);
}

