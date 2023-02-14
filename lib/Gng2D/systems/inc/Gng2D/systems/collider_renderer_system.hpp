#pragma once
#include <cmath>
#include "entt/entity/registry.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/types/scene.hpp"

namespace Gng2D
{
template <CircleColliderType Collider>
struct ColliderRendererSystem
{
    ColliderRendererSystem(Gng2D::Scene& s)
        : scene(s)
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
        for (const auto& [_, collider, position] : scene.view<Collider, Position>())
        {
            for (int r = collider.radius; r > 0; r--) drawCircle(r, position.x, position.y);
            SDL_RenderDrawPoint(renderer, position.x, position.y);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    };

private:
    Gng2D::Scene& scene;
    SDL_Renderer* renderer = scene.getRenderer();
};
}
