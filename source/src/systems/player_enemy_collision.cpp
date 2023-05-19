#include "systems/player_enemy_collision.hpp"
#include "components/invulnerability.hpp"
#include "components/destroyed_by_player.hpp"
#include "entities/red_x.hpp"

void PlayerEnemyCollision::onOverlap(Gng2D::GameObject player, Gng2D::GameObject enemy)
{ 
    enemy.addComponent<DestroyedByPlayer>();
    scene.destroyEntity(enemy.getId());

    if (not player.hasComponents<Invulnerability>())
    {
        player.addComponent<Invulnerability>(150u);
        auto& hp = player.getComponent<HitPoints>().value;
        hp -= 1;
    }
}

