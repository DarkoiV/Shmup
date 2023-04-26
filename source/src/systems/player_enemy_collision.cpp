#include "systems/player_enemy_collision.hpp"
#include "components/invulnerability.hpp"
#include "entities/red_x.hpp"

void PlayerEnemyCollision::onOverlap(entt::entity player, entt::entity enemy)
{ 
    auto enemyObject = scene.getGameObject(enemy);
    auto pos = enemyObject.getComponent<Gng2D::Position>();
    scene.spawnObject<RedX>(pos);
    scene.destroyEntity(enemy);
    auto playerObject = scene.getGameObject(player);

    if (not playerObject.hasComponents<Invulnerability>())
    {
        playerObject.addComponent<Invulnerability>(150u);
        auto& hp = playerObject.getComponent<HitPoints>().value;
        hp -= 1;
    }
}

