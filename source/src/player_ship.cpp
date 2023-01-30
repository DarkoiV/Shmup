#include "player_ship.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"

PlayerShip::PlayerShip(entt::registry& reg)
    : Gng2D::GameObject(reg)
{
    registry.emplace<Gng2D::Position>(id, 320.0f, 200.0f);
    registry.emplace<Gng2D::Sprite>(id, "data/Clojure.png", 0.25f);
}
