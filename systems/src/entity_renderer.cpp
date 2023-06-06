#include "Gng2D/systems/entity_renderer.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/roation.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/types/scene.hpp"

using namespace Gng2D;

EntityRenderer::EntityRenderer(entt::registry& r)
    : reg(r)
{
    reg.on_construct<Sprite>()
        .connect<&EntityRenderer::markForSorting>(this);
    reg.on_update<Sprite>()
        .connect<&EntityRenderer::markForSorting>(this);
    reg.on_destroy<Sprite>()
        .connect<&EntityRenderer::markForSorting>(this);

    reg.on_construct<Layer>()
        .connect<&EntityRenderer::markForSorting>(this);
    reg.on_update<Layer>()
        .connect<&EntityRenderer::markForSorting>(this);
    reg.on_destroy<Layer>()
        .connect<&EntityRenderer::markForSorting>(this);
}

EntityRenderer::~EntityRenderer()
{
    reg.on_construct<Sprite>()
        .disconnect<&EntityRenderer::markForSorting>(this);
    reg.on_update<Sprite>()
        .disconnect<&EntityRenderer::markForSorting>(this);
    reg.on_destroy<Sprite>()
        .disconnect<&EntityRenderer::markForSorting>(this);

    reg.on_construct<Layer>()
        .disconnect<&EntityRenderer::markForSorting>(this);
    reg.on_update<Layer>()
        .disconnect<&EntityRenderer::markForSorting>(this);
    reg.on_destroy<Layer>()
        .disconnect<&EntityRenderer::markForSorting>(this);
}

void EntityRenderer::operator()(SDL_Renderer* renderer)
{
    if (needsSorting) sortRenderables();
    reg.group<Sprite, Position>().each([renderer, this](entt::entity entity, Sprite& sprite, Position& pos)
    {
        SDL_Rect dstRect;
        SDL_SetTextureAlphaMod(sprite.texture, sprite.opacity);

        dstRect.w = sprite.srcRect.w * sprite.scale;
        dstRect.h = sprite.srcRect.h * sprite.scale;
        dstRect.x = static_cast<int>(pos.x) - dstRect.w / 2;
        dstRect.y = static_cast<int>(pos.y) - dstRect.h / 2;

        double angle = 0;
        if (auto* rotation = reg.try_get<Rotation>(entity))
        {
            angle = rotation->angle;
        }
            
        SDL_RenderCopyEx(renderer, sprite.texture, &sprite.srcRect, 
                         &dstRect, angle, nullptr, SDL_FLIP_NONE);
    });
}

void EntityRenderer::markForSorting()
{
    needsSorting = true;
}

void EntityRenderer::sortRenderables()
{
    renderables.sort([&](entt::entity lhs, entt::entity rhs)
    {
        bool leftHasLayer  = reg.all_of<Layer>(lhs);
        bool rightHasLayer = reg.all_of<Layer>(rhs);
        if (not rightHasLayer) return false;
        if (not leftHasLayer)  return true;
        return reg.get<Layer>(lhs) < reg.get<Layer>(rhs);
    });
    reg.sort<Rotation, Sprite>();

    needsSorting = false;
}

