#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/internal/window.hpp"

Gng2D::Scene::Scene()
    : sceneRenderer(Window::renderer())
{
}

void Gng2D::Scene::render()
{
    auto view = entityRegistry.view<Sprite, Position>();
    for (const auto& [_, sprite, pos] : view.each())
    {
        SDL_Rect dstRect;
        dstRect.w = sprite.srcRect.w * sprite.scale;
        dstRect.h = sprite.srcRect.h * sprite.scale;
        dstRect.x = static_cast<int>(pos.x) - (dstRect.w / 2);
        dstRect.y = static_cast<int>(pos.y) - (dstRect.h / 2);
            
        SDL_RenderCopy(sceneRenderer, sprite.texture, &sprite.srcRect, &dstRect);
    }

    SDL_RenderPresent(sceneRenderer);
    SDL_Delay(20);
};

void Gng2D::Scene::setNextScene(const std::string& name)
{ 
    sceneRegistry.setNextScene(name);
}

