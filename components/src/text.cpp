#include "Gng2D/components/text.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/sprite.hpp"

using Gng2D::Text;

Text::Text(const std::string& font, const std::string& str, float scale)
    : font(Gng2D::AssetRegistry().getFont(font))
    , str(str)
    , scale(scale)
{
    generateNewTexture();
}

SDL_Texture* Text::getSprite() const
{
    return textSprite.get();
}

float Text::getScale() const
{
    return scale;
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

void Text::changeScale(float s)
{
    scale = s;
    generateNewTexture();
}

void Text::changeRGBAMod(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
{
    red     = r;
    green   = g;
    blue    = b;
    alpha   = a;
    generateNewTexture();
}

void Text::generateNewTexture()
{
    int textWidth  = font.width() * str.size();
    int textHeight = font.height();

    auto newSprite = AssetRegistry::RenderToTexture(textWidth, textHeight, [this](SDL_Renderer* r)
    {
        SDL_Rect dst{0,0, font.width(), font.height()};
        for (const auto c : str)
        {
            font.renderChar(r, c, dst, red, green, blue, alpha);
            dst.x += dst.w;
        }
    }).getTexture();

    textSprite = OwnedTexture(newSprite, &SDL_DestroyTexture);
}

