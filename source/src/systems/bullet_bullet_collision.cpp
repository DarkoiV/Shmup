#include "systems/bullet_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"

void BulletBulletCollision::onOverlap(entt::entity b1, entt::entity b2)
{
    scene.destroyEntity(b1);
    scene.destroyEntity(b2);
}
