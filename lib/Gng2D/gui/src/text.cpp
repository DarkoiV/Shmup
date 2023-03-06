#include "Gng2D/gui/text.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/settings.hpp"

using namespace Gng2D::gui;

Text::Text(const std::string& font, const std::string& str)
    : font(AssetRegistry().getFont(font))
    , str(str)
{
}

void Text::render(SDL_Renderer* r) const
{
    SDL_Rect dst = {originPointX, 
                    originPointY, 
                    font.width()  * static_cast<int>(scale), 
                    font.height() * static_cast<int>(scale)};
    for(const char& c : str)
    {
        font.renderChar(r, c, dst, opacity);
        dst.x += font.width() * static_cast<int>(scale);
    }
}

void Text::setOriginPoint(int x, int y)
{
    originPointX = x;
    originPointY = y;
}

void Text::setPosition(Align a, int x, int y)
{
    if (a == Align::Center)
    {
        x = (SCREEN_WIDTH  / 2) - (width()  / 2) + x;
        y = (SCREEN_HEIGHT / 2) - (height() / 2) + y;
    }

    setOriginPoint(x, y);
}

void Text::setScale(unsigned s)
{
    scale = s;
}

void Text::setOpacity(uint8_t o)
{
    opacity = o;
}

void Text::changeFont(const std::string& fname)
{
    font = AssetRegistry().getFont(fname);
}

int Text::width() const
{
    return font.width() * str.size() * scale;
}

int Text::height() const
{
    return font.height() * scale;
}

