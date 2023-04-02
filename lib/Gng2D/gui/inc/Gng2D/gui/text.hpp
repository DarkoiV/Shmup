#pragma once
#include <string>
#include "Gng2D/gui/element.hpp"
#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/types/font.hpp"

namespace Gng2D::gui
{
struct Text : Element
{
    Text(const std::string& font, const std::string& str);

    void    render(SDL_Renderer*)   const override;
    int     width()                 const override;
    int     height()                const override;

    void    changeFont(const std::string& font);
    void    changeString(const std::string& str);
    void    setColorMod(uint8_t r, uint8_t g, uint8_t b);

    template<typename Coro, typename... Args>
    void    addAnimation(Coro coro, Args&&... args)
    {
        animation = coro(*this, std::forward<Args>(args)...);
    }

private:
    Font                font;
    std::string         str;
    mutable Coroutine   animation;

    uint8_t     redMod{255};
    uint8_t     greenMod{255};
    uint8_t     blueMod{255};
};
}
