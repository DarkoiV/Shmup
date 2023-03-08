#include "systems/player_weapons.hpp"
#include "entities/bullet.hpp"

void PlayerWeapons::primaryFire()
{
    if (not remainingCooldown)
    {
        const auto& playerPosition = playerShip.getComponent<Gng2D::Position>();
        const Gng2D::Position bulletSpawnPosition{playerPosition.x, playerPosition.y - 15};
        scene.spawnObject<AllyBullet>(bulletSpawnPosition, Gng2D::Velocity{0, -4});
        remainingCooldown = cooldownFrames;
    }
}

void PlayerWeapons::operator()()
{
    if (remainingCooldown > 0)                  remainingCooldown--;
    if (scene.isKeyPressed(SDL_SCANCODE_Z))     primaryFire();
}
