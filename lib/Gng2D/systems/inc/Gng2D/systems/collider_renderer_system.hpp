#pragma once
#include <cmath>
#include "entt/entity/registry.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/scene.hpp"

namespace Gng2D
{
template <CircleColliderType Collider>
struct ColliderRendererSystem
{
    ColliderRendererSystem(entt::registry& r)
        : registry(r)
    {
    }

    void drawCircle(int radius, int centerX, int centerY)
    {
        constexpr auto NO_OF_POINTS = 36;
        constexpr auto STEP = 360/NO_OF_POINTS;
        std::array<SDL_Point, NO_OF_POINTS> points;
        for (int i = 0; i < NO_OF_POINTS; i++)
        {
            auto rad = (STEP * i) * (std::numbers::pi / 180);
            points[i].x = (cos(rad) * radius) + centerX; 
            points[i].y = (sin(rad) * radius) + centerY; 
        }
        SDL_RenderDrawLines(renderer, points.data(), points.size());
    }

    void operator()()
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        auto view = registry.view<Collider, Position>();
        for (const auto& [_, collider, position] : view.each())
        {
            drawCircle(collider.radius, position.x, position.y);
            if (collider.radius > 2) drawCircle(collider.radius - 1, position.x, position.y);
            if (collider.radius > 3) drawCircle(collider.radius - 2, position.x, position.y);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    };

private:
    entt::registry& registry;
    SDL_Renderer* renderer = Window::renderer();
};
}
