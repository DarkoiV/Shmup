#include "systems/player_enemy_collision.hpp"
#include "components/invulnerability.hpp"

void PlayerEnemyCollision::onOverlap(entt::entity player, entt::entity enemy)
{
    scene.destroyEntity(enemy);
    auto playerObject = scene.getEntity(player);

    if (not playerObject.hasComponents<Invulnerability>())
    {
        playerObject.addComponent<Invulnerability>(150u);
        auto& hp = playerObject.getComponent<HitPoints>().value;
        hp -= 1;
    }
}

