#include "bullet_bullet_collision_system.hpp"

void BulletBulletCollisionSystem::onOverlap(entt::entity b1, entt::entity b2)
{
    registry.destroy(b1);
    registry.destroy(b2);
}
