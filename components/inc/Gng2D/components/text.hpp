#pragma once
#include <string>
#include <memory>
#include "Gng2D/types/font.hpp"

namespace Gng2D 
{
struct GameObject;
struct Text 
{
    Text(const std::string& font, const std::string& str, float scale = 1.0f);

    SDL_Texture*    getSprite() const;
    float           getScale() const;
    void            changeFont(const std::string& font);
    void            changeString(const std::string& str);
    void            changeScale(float);
    void            changeRGBAMod(uint8_t, uint8_t, uint8_t, uint8_t);

private:
    using OwnedTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
    void generateNewTexture();

    Font            font;
    std::string     str;
    float           scale;
    OwnedTexture    textSprite{nullptr, &SDL_DestroyTexture};

    uint8_t         red{255};
    uint8_t         green{255};
    uint8_t         blue{255};
    uint8_t         alpha{255};
};
}

