#pragma once
#include <string>
#include <tuple>
#include "Gng2D/gui/element.hpp"

namespace Gng2D::gui 
{
struct Box : ::Gng2D::gui::Element
{
    Box(const std::string& boxSprite);

    void    render(SDL_Renderer*) const;
    int     width() const;
    int     height() const;

    void    setCapacity(int width, int height, int margin = 0);
    std::pair<int, int> innerOrgin() const;

private:
    int boxTileWidth{0};
    int boxTileHeight{0};

    int capacityWidth{0};
    int capacityHeight{0};
    int capacityMargin{0};

    SDL_Texture* texture;
};
}

