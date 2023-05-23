#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/layer.hpp"
#include "sprite_sheets.hpp"
#include "flight_scene_layers.hpp"
#include "components/colliders.hpp"
#include "components/basic_weapon.hpp"
#include "components/invulnerability.hpp"
#include "components/hit_points.hpp"

PlayerControlls::PlayerControlls(Gng2D::Scene& s, entt::registry& r)
    : scene(s)
    , reg(r)
{
    playerShip = reg.create();
    auto& sprite = reg.emplace<Gng2D::Sprite>(playerShip, "player_ship", 1);
    PlayerSpriteSheet::divideSprite(sprite);
    reg.emplace<Gng2D::Position>(playerShip, 320.0f, 200.0f);
    reg.emplace<Gng2D::Velocity>(playerShip, 0.0f, 0.0f);
    reg.emplace<PlayerCollider>(playerShip, 6.0f);
    reg.emplace<HitPoints>(playerShip, 5u, 5u);
    reg.emplace<Gng2D::Layer>(playerShip, FlightSceneLayer::Ships);
    reg.emplace<BasicWeapon>(playerShip);
}

void PlayerControlls::playerMovement()
{
    auto& velo      = reg.get<Gng2D::Velocity>(playerShip);
    auto& sprite    = reg.get<Gng2D::Sprite>(playerShip);
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
    auto& pos = reg.get<Gng2D::Position>(playerShip);
    if (pos.x < 0)                       pos.x = 0;
    if (pos.y < 0)                       pos.y = 0;
    if (pos.x > Gng2D::SCREEN_WIDTH)     pos.x = Gng2D::SCREEN_WIDTH;
    if (pos.y > Gng2D::SCREEN_HEIGHT)    pos.y = Gng2D::SCREEN_HEIGHT;
}

void PlayerControlls::primaryFire()
{
    const bool fire = scene.isKeyPressed(SDL_SCANCODE_Z);

    for (auto&& [_, weapon, pos] : reg.view<BasicWeapon, Gng2D::Position>().each())
    {
        if (weapon.remainigCooldown > 0) weapon.remainigCooldown--;

        if (fire and not weapon.remainigCooldown)
        {
            const Gng2D::Position bulletPos{pos.x, pos.y - 7};
            const Gng2D::Velocity bulletVel{0, -4};
            spawnBullet(bulletPos, bulletVel);
            weapon.remainigCooldown = weapon.cooldownTicks;
        }
    }
}

void PlayerControlls::invulnerabilityAnimation()
{
    auto& sprite = reg.get<Gng2D::Sprite>(playerShip);
    if (reg.any_of<Invulnerability>(playerShip))
    {
        auto& inv = reg.get<Invulnerability>(playerShip);
        if (inv.ticksRemaining == 0) 
        {
            reg.remove<Invulnerability>(playerShip);
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

void PlayerControlls::spawnBullet(Gng2D::Position pos, Gng2D::Velocity vel)
{
    auto bullet = reg.create();
    reg.emplace<Gng2D::Sprite>(bullet, "ally_bullet");
    reg.emplace<Gng2D::Position>(bullet, pos);
    reg.emplace<Gng2D::Velocity>(bullet, vel);
    reg.emplace<PlayerBulletCollider>(bullet, 4.0f);
    reg.emplace<Gng2D::Layer>(bullet, FlightSceneLayer::Bullets);
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

