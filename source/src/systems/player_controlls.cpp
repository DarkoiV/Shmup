#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/scene/scene.hpp"
#include "sprite_sheets.hpp"
#include "flight_scene_layers.hpp"
#include "components/colliders.hpp"
#include "components/basic_weapon.hpp"
#include "components/invulnerability.hpp"

PlayerControlls::PlayerControlls(entt::registry& r)
    : reg(r)
    , scene(reg.ctx().get<Gng2D::Scene&>())
{
    playerShip = scene.newEntity()
        .with<Gng2D::Position>(320.0f, 200.0f)
        .with<Gng2D::Velocity>(0.0f, 0.0f)
        .with<PlayerCollider>(6.0f)
        .with<HitPoints>(5u, 5u)
        .with<Gng2D::Layer>(FlightSceneLayer::Ships)
        .with<BasicWeapon>()
        .with<Gng2D::Sprite>("player_ship", 1)
        .with<Gng2D::NameTag>("Player")
        .modify<Gng2D::Sprite>([](auto& sprite)
        {
            PlayerSpriteSheet::divideSprite(sprite);
        })
        .get();
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
    scene.newEntity()
        .with<Gng2D::Sprite>("ally_bullet")
        .with<Gng2D::Position>(pos)
        .with<Gng2D::Velocity>(vel)
        .with<PlayerBulletCollider>(4.0f)
        .with<Gng2D::Layer>(FlightSceneLayer::Bullets);
}

void PlayerControlls::hpControl()
{
    auto& playerHP = reg.get<HitPoints>(playerShip);
    if (playerHP.max == cachedHP.max 
    and playerHP.value == cachedHP.value) return;
    cachedHP = playerHP;

    if (hpDisplay != entt::null) reg.destroy(hpDisplay);

    hpDisplay = scene.newEntity()
        .with<Gng2D::Position>(620.0f, 15.0f)
        .get();

    for(unsigned i = 1; i <= playerHP.max; i++)
    {
        scene.newEntity()
            .withParent(hpDisplay)
            .with<Gng2D::Layer>(static_cast<uint8_t>(100))
            .with<Gng2D::RelativePosition>(-16.0f * i, 0.0f)
            .with<Gng2D::Sprite>("hitpoints")
            .modify<Gng2D::Sprite>([i, &playerHP](auto& sprite)
            {
                sprite.srcRect.w /= 2;
                if (i > playerHP.value) 
                    sprite.srcRect.x += sprite.srcRect.w;
                sprite.opacity = 155;
            });
    }
}

bool PlayerControlls::inFocusMode() const
{
    return focusMode;
}

bool PlayerControlls::isPlayerAlive() const
{
    return reg.get<HitPoints>(playerShip).value > 0;
}

void PlayerControlls::operator()()
{
    focusMode = scene.isKeyPressed(SDL_SCANCODE_LSHIFT);

    playerMovement();
    boundPlayerPosition();
    primaryFire();
    invulnerabilityAnimation();
    hpControl();
}

