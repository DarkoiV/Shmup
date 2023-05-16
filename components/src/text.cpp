#include "Gng2D/components/text.hpp"
#include "Gng2D/core/asset_registry.hpp"

using Gng2D::Text;

Text::Text(const std::string& font, const std::string& str)
    : font(Gng2D::AssetRegistry().getFont(font))
    , str(str)
{
    generateNewTexture();
}

Text::~Text()
{
    SDL_DestroyTexture(textSprite);
}

SDL_Texture* Text::getSprite() const
{
    return textSprite;
}

void Text::changeFont(const std::string& f)
{
    font = AssetRegistry().getFont(f);
    generateNewTexture();
}

void Text::changeString(const std::string& s)
{
    str = s;
    generateNewTexture();
}

void Text::generateNewTexture()
{
    if (textSprite)
    {
        SDL_DestroyTexture(textSprite);
        textSprite = nullptr;
    }

    int textWidth  = font.width() * str.size();
    int textHeight = font.height();

    textSprite = AssetRegistry::RenderToTexture(textWidth, textHeight).renderCommands([this](SDL_Renderer* r)
    {
        SDL_Rect dst{0,0, font.width(), font.height()};
        for (const auto c : str)
        {
            font.renderChar(r, c, dst, 255, 255, 255, 255);
            dst.x += dst.w;
        }
    }).getTexture();
}

