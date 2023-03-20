#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/types/scene.hpp"

using namespace Gng2D;

EntityRenderer::EntityRenderer(Scene& s)
    : scene(s)
{
}

void EntityRenderer::operator()(SDL_Renderer* r)
{
    for (const auto& [_, sprite, pos] : scene.view<Sprite, Position>())
    {
        SDL_Rect dstRect;
        SDL_SetTextureAlphaMod(sprite.texture, sprite.opacity);

        dstRect.w = sprite.srcRect.w * sprite.scale;
        dstRect.h = sprite.srcRect.h * sprite.scale;
        dstRect.x = static_cast<int>(pos.x) - dstRect.w / 2;
        dstRect.y = static_cast<int>(pos.y) - dstRect.h / 2;
            
        SDL_RenderCopy(r, sprite.texture, &sprite.srcRect, &dstRect);
    }
}

