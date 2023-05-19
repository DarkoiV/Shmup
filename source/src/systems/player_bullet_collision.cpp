#include "systems/player_bullet_collision.hpp"
#include "Gng2D/core/log.hpp"
#include "components/invulnerability.hpp"

void PlayerBulletCollision::onOverlap(Gng2D::GameObject player, Gng2D::GameObject bullet)
{
    scene.destroyEntity(bullet.getId());

    if (not player.hasComponents<Invulnerability>())
    {
        player.addComponent<Invulnerability>(150u);
        auto& hp = player.getComponent<HitPoints>().value;
        hp -= 1;
    }
}

