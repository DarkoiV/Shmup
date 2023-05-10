#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"
#include "components/basic_weapon.hpp"
#include "components/invulnerability.hpp"
#include "entities/bullet.hpp"

void PlayerControlls::playerMovement()
{
    auto& velo      = playerShip.getComponent<Gng2D::Velocity>();
    auto& sprite    = playerShip.getComponent<Gng2D::Sprite>();
    velo            = {0, 0};
    const float speedMod  = focusMode ? 0.5f : 1.0f;
    const float shipSpeed = 3.0f;

    if (scene.isKeyPressed(SDL_SCANCODE_DOWN))    velo.y += shipSpeed * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_UP))      velo.y -= shipSpeed * speedMod;
    const bool right  = scene.isKeyPressed(SDL_SCANCODE_RIGHT);
    const bool left   = scene.isKeyPressed(SDL_SCANCODE_LEFT);
    if (right)
    {
        velo.x += shipSpeed * speedMod;
        PlayerSpriteSheet::setHFrame(PlayerSpriteSheet::HFrame::Right, sprite);
    }
    if (left)
    {
        velo.x -= shipSpeed * speedMod;
        PlayerSpriteSheet::setHFrame(PlayerSpriteSheet::HFrame::Left, sprite);
    }
    if (right == left) PlayerSpriteSheet::setHFrame(PlayerSpriteSheet::HFrame::Forward, sprite);

}

void PlayerControlls::boundPlayerPosition()
{
    auto& pos = playerShip.getComponent<Gng2D::Position>();

    if (pos.x < 0)                       pos.x = 0;
    if (pos.y < 0)                       pos.y = 0;
    if (pos.x > Gng2D::SCREEN_WIDTH)     pos.x = Gng2D::SCREEN_WIDTH;
    if (pos.y > Gng2D::SCREEN_HEIGHT)    pos.y = Gng2D::SCREEN_HEIGHT;
}

void PlayerControlls::primaryFire()
{
    const bool fire = scene.isKeyPressed(SDL_SCANCODE_Z);

    for (const auto [_, weapon, pos] : scene.view<BasicWeapon, Gng2D::Position>())
    {
        if (weapon.remainigCooldown > 0) weapon.remainigCooldown--;

        if (fire and not weapon.remainigCooldown)
        {
            const Gng2D::Position bulletSpawnPosition{pos.x, pos.y - 7};
            const Gng2D::Velocity bulletVelocity{0, -4};
            scene.spawn<AllyBullet>(bulletSpawnPosition, bulletVelocity);
            weapon.remainigCooldown = weapon.cooldownTicks;
        }
    }
}

void PlayerControlls::invulnerabilityAnimation()
{
    auto& sprite    = playerShip.getComponent<Gng2D::Sprite>();
    if (playerShip.hasComponents<Invulnerability>())
    {
        auto& inv = playerShip.getComponent<Invulnerability>();
        if (inv.ticksRemaining == 0) 
        {
            playerShip.removeComponent<Invulnerability>();
            sprite.opacity = 255;
        }
        else
        {
            inv.ticksRemaining--;
            bool blinking = inv.ticksRemaining % 20 > 10;
            sprite.opacity = 200 - (100 * blinking);
        }
    }
}

bool PlayerControlls::inFocusMode() const
{
    return focusMode;
}

void PlayerControlls::operator()()
{
    focusMode = scene.isKeyPressed(SDL_SCANCODE_LSHIFT);

    playerMovement();
    boundPlayerPosition();
    primaryFire();
    invulnerabilityAnimation();
}

