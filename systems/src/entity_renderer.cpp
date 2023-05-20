#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/types/scene.hpp"

using namespace Gng2D;


EntityRenderer::EntityRenderer(Scene& s)
    : scene(s)
{
    scene.group<Sprite, Position>();
    scene.onConstruct<Sprite>().connect<&EntityRenderer::markForSorting>(this);
    scene.onConstruct<Layer>().connect<&EntityRenderer::markForSorting>(this);
    scene.onUpdate<Layer>().connect<&EntityRenderer::markForSorting>(this);
}

EntityRenderer::~EntityRenderer()
{
    scene.onConstruct<Sprite>().disconnect<&EntityRenderer::markForSorting>(this);
    scene.onConstruct<Layer>().disconnect<&EntityRenderer::markForSorting>(this);
    scene.onUpdate<Layer>().disconnect<&EntityRenderer::markForSorting>(this);
}

void EntityRenderer::operator()(SDL_Renderer* r)
{
    if (needsSorting) sortRenderables();
    for (const auto& [_, sprite, pos] : scene.group<Sprite, Position>())
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

void EntityRenderer::markForSorting()
{
    needsSorting = true;
}

void EntityRenderer::sortRenderables()
{
    auto renderables = scene.group<Sprite, Position>();
    renderables.sort([](GameObject lhs, GameObject rhs)
    {
        bool leftHasLayer  = lhs.hasComponents<Layer>();
        bool rightHasLayer = rhs.hasComponents<Layer>();
        if (not rightHasLayer) return false;
        if (not leftHasLayer)  return true;
        return lhs.getComponent<Layer>().value < rhs.getComponent<Layer>().value;
    });

    needsSorting = false;
}

