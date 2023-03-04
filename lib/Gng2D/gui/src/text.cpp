#include "Gng2D/gui/text.hpp"
#include <ranges>
#include "Gng2D/core/asset_registry.hpp"

using namespace Gng2D::gui;

Text::Text(const std::string& font, const std::string& str)
    : font(AssetRegistry().getFont(font))
    , str(str)
{
}

void Text::render(SDL_Renderer* r, int originPointX, int originPointY)
{
    SDL_Rect dst = {originPointX, 
                    originPointY, 
                    font.charWidth  * static_cast<int>(scale), 
                    font.charHeight * static_cast<int>(scale)};
    for(const char& c : str)
    {
        font.renderChar(r, c, dst);
        dst.x += font.charWidth * static_cast<int>(scale);
    }
}

void Text::setScale(unsigned s)
{
    scale = s;
}

int Text::width()
{
    return font.charWidth * str.size();
}

int Text::height()
{
    return font.charHeight;
}

