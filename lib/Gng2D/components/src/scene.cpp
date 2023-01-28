#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Gng2D/internal/window.hpp"
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/position.hpp"

Gng2D::Scene::Scene()
    : sceneRenderer(Window::renderer())
{
    // TMP TEST
    for (int i = 0; i < 10; i++)
    {
        SDL_Rect rect;
        rect.x = 20 + 50 * i;
        rect.y = 20 + 50 * i;
        rect.w = 50 + i;
        rect.h = 50 + i;
        const auto entity = registry.create();
        registry.emplace<Position>(entity, i * 30.f, i * 30.f);
        registry.emplace<Sprite>(entity, "data/Clojure.png", rect);
    }
}

void Gng2D::Scene::render()
{
    auto view = registry.view<const Sprite, const Position>();
    for (const auto& [_, sprite, pos] : view.each())
    {
        SDL_Rect dstRect;
        dstRect.x = static_cast<int>(pos.x) + (sprite.srcRect.w / 2);
        dstRect.y = static_cast<int>(pos.y) + (sprite.srcRect.h / 2);
        dstRect.w = sprite.srcRect.w;
        dstRect.h = sprite.srcRect.h;
            
        SDL_RenderCopy(sceneRenderer, sprite.texture, &sprite.srcRect, &dstRect);
    }

    SDL_RenderPresent(sceneRenderer);
    SDL_Delay(20);
};
