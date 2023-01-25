#include <SDL2/SDL.h>
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/position.hpp"

void Gng2D::Scene::render()
{
    auto view = registry.view<const Sprite, const Position>();
    view.each([this](const auto& sprite, const auto& pos)
    {
        SDL_Rect dstRect;
        dstRect.x = pos.x + (sprite.srcRect.w / 2);
        dstRect.y = pos.y + (sprite.srcRect.h / 2);
        dstRect.w = sprite.srcRect.w;
        dstRect.h = sprite.srcRect.h;
            
        SDL_RenderCopy(sceneRenderer, sprite.texture, &sprite.srcRect, &dstRect);
    });

    SDL_RenderPresent(sceneRenderer);
    SDL_Delay(20);
};
