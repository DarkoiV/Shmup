#include <SDL2/SDL_image.h>
#include "Gng2D/core/render_system.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/position.hpp"

Gng2D::RenderSystem::RenderSystem(entt::registry& reg)
    : registry(reg)
    , targetRenderer(Window::renderer())
{
    // TMP TEST
    auto text = IMG_LoadTexture(targetRenderer, "data/Clojure.png");
    for (int i = 0; i < 10; i++)
    {
        SDL_Rect rect;
        rect.x = 20 + 50 * i;
        rect.y = 20 + 50 * i;
        rect.w = 50 + i;
        rect.h = 50 + i;
        const auto entity = registry.create();
        registry.emplace<Position>(entity, i * 30.f, i * 30.f);
        registry.emplace<Sprite>(entity, text, rect);
    }
}

void Gng2D::RenderSystem::operator()() const
{
    auto view = registry.view<const Sprite, const Position>();
    view.each([this](const auto& sprite, const auto& pos)
    {
        SDL_Rect dstRect;
        dstRect.x = pos.x + (sprite.srcRect.w / 2);
        dstRect.y = pos.y + (sprite.srcRect.h / 2);
        dstRect.w = sprite.srcRect.w;
        dstRect.h = sprite.srcRect.h;
            
        SDL_RenderCopy(targetRenderer, sprite.texture, &sprite.srcRect, &dstRect);
    });

    SDL_RenderPresent(targetRenderer);
    SDL_Delay(20);
}
