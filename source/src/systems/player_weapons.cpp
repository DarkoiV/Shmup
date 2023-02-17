#include "systems/player_weapons.hpp"
#include "entities/bullet.hpp"

PlayerWeapons::PlayerWeapons(Gng2D::Scene& s, PlayerShip& ps)
    : scene(s)
    , playerShip(ps)
{
}

void PlayerWeapons::primaryFire()
{
    if (not remainingCooldown)
    {
        const auto playerPosition = playerShip.getComponent<Gng2D::Position>();
        const auto ipos = playerPosition(0);
        const Gng2D::Position bulletSpawnPosition{ipos.x, ipos.y - 10};
        scene.spawnObject<AllyBullet>(bulletSpawnPosition, Gng2D::Velocity{0, -7});
        remainingCooldown = cooldownFrames;
    }
}

void PlayerWeapons::operator()()
{
    if (remainingCooldown > 0) remainingCooldown--;
}
