#pragma once
#include <string>
#include "Gng2D/types/font.hpp"

namespace Gng2D 
{
struct GameObject;
struct TextSprite 
{
    TextSprite(const std::string& font, const std::string& str, float scale = 1.0f);
    ~TextSprite();

    void onAttach(Gng2D::GameObject);

    SDL_Texture*    getSprite() const;
    float           getScale() const;
    void            changeFont(const std::string& font);
    void            changeString(const std::string& str);
    void            changeScale(float);

private:
    void generateNewTexture();

    Font            font;
    std::string     str;
    float           scale;
    SDL_Texture*    textSprite{};

    uint8_t         red{255};
    uint8_t         green{255};
    uint8_t         blue{255};
    uint8_t         alpha{255};
};
}

