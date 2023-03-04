#include "Gng2D/core/log.hpp"
#include "Gng2D/types/font.hpp"

using namespace Gng2D;

Font::Font(SDL_Texture* t, int cw, int ch, int cpr)
    : charWidth(cw)
    , charHeight(ch)
    , charsPerRow(cpr)
    , fontTexutre(t)
{
    LOG::INFO("Loaded font dimensions", charWidth, charHeight, charsPerRow);
}

Font::Font(const Font& from)
    : charWidth(from.charWidth)
    , charHeight(from.charHeight)
    , charsPerRow(from.charsPerRow)
    , fontTexutre(from.fontTexutre)
{
}

void Font::renderChar(SDL_Renderer* r, char c, SDL_Rect dst)
{
    const char offsetedChar = c - 32;
    int srcx = offsetedChar % charsPerRow * charWidth;
    int srcy = offsetedChar / charsPerRow * charHeight;
    SDL_Rect src = {srcx, srcy, charWidth, charHeight};
    SDL_RenderCopy(r, fontTexutre, &src, &dst);
}
