#include "Gng2D/components/text_sprite.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/sprite.hpp"

using Gng2D::TextSprite;

TextSprite::TextSprite(const std::string& font, const std::string& str, float scale)
    : font(Gng2D::AssetRegistry().getFont(font))
    , str(str)
    , scale(scale)
{
    generateNewTexture();
}

TextSprite::~TextSprite()
{
    SDL_DestroyTexture(textSprite);
}

void TextSprite::onAttach(Gng2D::GameObject owner)
{
    owner.addComponent<Sprite>(*this);
}

SDL_Texture* TextSprite::getSprite() const
{
    return textSprite;
}

float TextSprite::getScale() const
{
    return scale;
}

void TextSprite::changeFont(const std::string& f)
{
    font = AssetRegistry().getFont(f);
    generateNewTexture();
}

void TextSprite::changeString(const std::string& s)
{
    str = s;
    generateNewTexture();
}

void TextSprite::changeScale(float s)
{
    scale = s;
}

void TextSprite::generateNewTexture()
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

