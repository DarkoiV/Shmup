#include "Gng2D/core/render_system.hpp"
#include "Gng2D/core/log.hpp"

struct Sprite
{
    std::string name;
};

struct Position
{
    float x;
    float y;
};

Gng2D::RenderSystem::RenderSystem(entt::registry& reg)
    : registry(reg)
{
    // TMP TEST
    for (int i = 0; i < 10; i++)
    {
        const auto entity = registry.create();
        registry.emplace<Position>(entity, i * 1.f, i * 1.f);
        registry.emplace<Sprite>(entity, std::string("namae wa " + std::to_string(i)));
    }
}

void Gng2D::RenderSystem::operator()() const
{
    auto view = registry.view<const Sprite, const Position>();
    view.each([](const auto& sprite, const auto& pos)
    {
        LOG::INFO(sprite.name, pos.x, "x", pos.y);
    });

    SDL_Delay(20);
}
