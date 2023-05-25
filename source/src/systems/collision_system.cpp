#include "systems/collision_system.hpp"
#include "components/hit_points.hpp"
#include "components/invulnerability.hpp"

CollisionSystem::CollisionSystem(entt::registry& r)
    : bulletBullet(r)
    , playerEnemy(r)
    , bulletEnemy(r)
    , bulletPlayer(r)
{
}

void CollisionSystem::operator()()
{
    bulletBullet();
    playerEnemy();
    bulletEnemy();
    bulletPlayer();
}

void CollisionSystem::BulletBullet::onOverlap(entt::entity bullet1, entt::entity bullet2)
{
    reg.destroy(bullet1);
    reg.destroy(bullet2);
}

void CollisionSystem::PlayerEnemy::onOverlap(entt::entity player, entt::entity enemy)
{
    reg.destroy(enemy);

    if (not reg.all_of<Invulnerability>(player))
    {
        auto& HP = reg.get<HitPoints>(player).value;
        HP--;
        reg.emplace<Invulnerability>(player, 150u);
    }
}

void CollisionSystem::BulletEnemy::onOverlap(entt::entity bullet, entt::entity enemy)
{
    reg.destroy(bullet);
    auto& HP = reg.get<HitPoints>(enemy).value;
    HP--;
    
    if(HP == 0) reg.destroy(enemy);
}

void CollisionSystem::BulletPlayer::onOverlap(entt::entity bullet, entt::entity player)
{
    reg.destroy(bullet);

    if (not reg.all_of<Invulnerability>(player))
    {
        auto& HP = reg.get<HitPoints>(player).value;
        HP--;
        reg.emplace<Invulnerability>(player, 150u);
    }
}

