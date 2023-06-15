#include "systems/collision_system.hpp"
#include "systems/entity_factory.hpp"
#include "components/destroy.hpp"
#include "components/hit_points.hpp"
#include "components/invulnerability.hpp"
#include "components/pickup.hpp"
#include "Gng2D/components/animation.hpp"
#include "Gng2D/core/log.hpp"
#include "animations.hpp"

static inline void damagePlayer(entt::registry& reg, entt::entity player)
{
    if (not reg.all_of<Invulnerability>(player))
    {
        auto& HP = reg.get<HitPoints>(player).value;
        HP--;
        reg.emplace<Invulnerability>(player, 150u);
    }
}

CollisionSystem::CollisionSystem(entt::registry& r)
    : bulletBullet(r)
    , playerEnemy(r)
    , playerPickup(r)
    , bulletEnemy(r)
    , bulletPlayer(r)
    , laserPlayer(r)
{
}

void CollisionSystem::operator()()
{
    bulletBullet();
    playerEnemy();
    playerPickup();
    bulletEnemy();
    bulletPlayer();
    laserPlayer();
}

void CollisionSystem::BulletBullet::onOverlap(entt::entity bullet1, entt::entity bullet2)
{
    reg.destroy(bullet1);
    reg.destroy(bullet2);
}

void CollisionSystem::PlayerEnemy::onOverlap(entt::entity player, entt::entity enemy)
{
    reg.emplace<Destroy>(enemy, Destroy::Effect::spawnRedX);
    damagePlayer(reg, player);
}

void CollisionSystem::PlayerPickup::onOverlap(entt::entity player, entt::entity pickup)
{
    auto type = reg.get<Pickup>(pickup).type;
    switch (type)
    {
        case Pickup::Type::drones:
            EntityFactory(reg).spawnDrone(player, {-22, 5});
            EntityFactory(reg).spawnDrone(player, {22, 5});
            break;
    }
    reg.destroy(pickup);
}

void CollisionSystem::BulletEnemy::onOverlap(entt::entity bullet, entt::entity enemy)
{
    reg.destroy(bullet);
    auto& HP = reg.get<HitPoints>(enemy).value;
    HP--;
    
    if(HP == 0) reg.emplace<Destroy>(enemy, Destroy::Effect::spawnRedX);
    else emplaceAnimation(flashShip, reg, enemy);
}

void CollisionSystem::BulletPlayer::onOverlap(entt::entity bullet, entt::entity player)
{
    reg.destroy(bullet);
    damagePlayer(reg, player);
}

void CollisionSystem::LaserPlayer::onOverlap(entt::entity, entt::entity player)
{
    damagePlayer(reg, player);
}

