#include "systems/player_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"

void PlayerBulletCollision::onOverlap(entt::entity, entt::entity)
{
    Gng2D::LOG::INFO("Collision!!!");
}
