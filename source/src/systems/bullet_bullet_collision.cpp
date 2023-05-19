#include "systems/bullet_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"

void BulletBulletCollision::onOverlap(Gng2D::GameObject b1, Gng2D::GameObject b2)
{
    scene.destroyEntity(b1.getId());
    scene.destroyEntity(b2.getId());
}

