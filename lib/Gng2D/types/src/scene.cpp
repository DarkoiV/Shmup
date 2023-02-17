#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Gng2D/components/position.hpp"
#include "Gng2D/types/scene.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/window.hpp"

void Gng2D::Scene::render(uint32_t msLag)
{
    auto view = registry.view<Sprite, Position>();
    for (const auto& [_, sprite, pos] : view.each())
    {
        SDL_Rect dstRect;
        dstRect.w = sprite.srcRect.w * sprite.scale;
        dstRect.h = sprite.srcRect.h * sprite.scale;
        const auto ipos = pos(msLag);
        dstRect.x = ipos.x - (static_cast<float>(dstRect.w) / 2);
        dstRect.y = ipos.y - (static_cast<float>(dstRect.h) / 2);
            
        SDL_RenderCopy(sceneRenderer, sprite.texture, &sprite.srcRect, &dstRect);
    }
};

Gng2D::GameObject Gng2D::Scene::getEntity(entt::entity id)
{
    return GameObject(*this, id);
}

bool Gng2D::Scene::entityExists(entt::entity id) const
{
    return registry.valid(id);
}

void Gng2D::Scene::destroyEntity(entt::entity id)
{
    registry.destroy(id);
}

bool Gng2D::Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

SDL_Renderer* Gng2D::Scene::getRenderer() const
{
    return sceneRenderer;
}

