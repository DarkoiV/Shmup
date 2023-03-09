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
    virtual void    setOriginPoint(int x, int y)     = 0;
    virtual void    setPosition(Align, int x, int y) = 0;
    virtual void    setScale(unsigned)               = 0;
    virtual void    setOpacity(uint8_t)              = 0;
    virtual int     width()     const                = 0;
    virtual int     height()    const                = 0;

protected:
    int             originPointX{0};
    int             originPointY{0};
    unsigned        scale{1};
    uint8_t         opacity{255};
};
}
