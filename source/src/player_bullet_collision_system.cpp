#include "player_bullet_collision_system.hpp"
#include "Gng2D/core/log.hpp"

void PlayerBulletCollisionSystem::onOverlap(entt::entity, entt::entity)
{
    Gng2D::LOG::INFO("Collision!!!");
}
