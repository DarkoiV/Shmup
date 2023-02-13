#include "systems/player_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"

void PlayerBulletCollision::onOverlap(entt::entity player, entt::entity bullet)
{
    scene.destroyEntity(bullet);
    auto& [health] = scene.getEntity(player).getComponent<Stats>();
    health -= 10;
    if (health <= 0) Gng2D::LOG::INFO("SHIP DESTROYED!!");
}
