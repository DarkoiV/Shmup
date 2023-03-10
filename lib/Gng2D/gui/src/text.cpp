#include "Gng2D/gui/text.hpp"
#include "Gng2D/core/asset_registry.hpp"

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

