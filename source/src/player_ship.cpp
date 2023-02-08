#include "player_ship.hpp"
#include "Gng2D/components/acceleration.hpp"
#include "Gng2D/components/velocity.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/sprite.hpp"

PlayerShip::PlayerShip(entt::registry& reg)
    : Gng2D::GameObject(reg)
{
    addComponent<Gng2D::Position>(320.0f, 200.0f);
    addComponent<Gng2D::Acceleration>(0.0f, 0.0f);
    addComponent<Gng2D::Velocity>(0.0f, 0.0f, 5.0f, 0.3f);
    addComponent<Gng2D::Sprite>("player_ship");
    addComponent<PlayerCollider>(5.0f);
}
