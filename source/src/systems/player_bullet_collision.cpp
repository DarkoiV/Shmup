#include "systems/player_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"
#include "components/invulnerability.hpp"

void PlayerBulletCollision::onOverlap(entt::entity player, entt::entity bullet)
{
    scene.destroyEntity(bullet);
    auto playerObject = scene.getEntity(player);

    if (not playerObject.hasComponents<Invulnerability>())
    {
        playerObject.addComponent<Invulnerability>(150u);
        auto& hp = playerObject.getComponent<HitPoints>().value;
        hp -= 1;
    }
}
