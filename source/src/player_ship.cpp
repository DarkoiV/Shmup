#include "player_ship.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"

PlayerShip::PlayerShip(entt::registry& reg)
    : Gng2D::GameObject(reg)
{
    addComponent<Gng2D::Position>(320.0f, 200.0f);
    addComponent<Gng2D::Sprite>("player_ship");
}
