#pragma once
#include <SDL2/SDL.h>

namespace Gng2D::gui 
{
struct Element 
{
    enum class Align 
    {
        Center,
    };

    virtual void    render(SDL_Renderer*) const      = 0;
    virtual int     width()     const                = 0;
    virtual int     height()    const                = 0;

    void    setScale(unsigned); 
    void    setOpacity(uint8_t);
    void    setOriginPoint(int x, int y); 
    void    setPosition(Align, int x, int y);

protected:
    int             originPointX{0};
    int             originPointY{0};
    unsigned        scale{1};
    uint8_t         opacity{255};
};
}
