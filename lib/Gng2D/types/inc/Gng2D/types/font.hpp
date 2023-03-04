#pragma once
#include <SDL2/SDL.h>

namespace Gng2D
{
struct Font 
{
    Font(SDL_Texture*, int charWidth, int charHeight, int charsPerRow);
    Font(const Font&);
    Font(Font&&) = delete;
    Font& operator= (const Font&)  = delete;
    Font& operator= (const Font&&) = delete;

    void    renderChar(SDL_Renderer*, char, SDL_Rect dst);

    const int       charWidth;
    const int       charHeight;
    const int       charsPerRow;

private:
    SDL_Texture*    fontTexutre;
};
}

