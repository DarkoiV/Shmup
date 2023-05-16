#pragma once
#include <string>
#include "Gng2D/types/font.hpp"

namespace Gng2D 
{
struct Text 
{
    Text(const std::string& font, const std::string& str);
    ~Text();

    SDL_Texture*    getSprite() const;
    void            changeFont(const std::string& font);
    void            changeString(const std::string& str);

private:
    void generateNewTexture();

    Font            font;
    std::string     str;
    SDL_Texture*    textSprite{};

    uint8_t         red{255};
    uint8_t         green{255};
    uint8_t         blue{255};
    uint8_t         alpha{255};
};
}

