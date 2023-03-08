#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"

void PlayerControlls::playerControlls()
{
    auto& velo      = playerShip.getComponent<Gng2D::Velocity>();
    auto& sprite    = playerShip.getComponent<Gng2D::Sprite>();
    velo            = {0, 0};
    float speedMod  = focusMode ? 0.5f : 1.0f;
    float shipSpeed = 3.0f;

    if (scene.isKeyPressed(SDL_SCANCODE_DOWN))    velo.y += shipSpeed * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_UP))      velo.y -= shipSpeed * speedMod;
    const bool right  = scene.isKeyPressed(SDL_SCANCODE_RIGHT);
    const bool left   = scene.isKeyPressed(SDL_SCANCODE_LEFT);
    if (right)
    {
        velo.x += shipSpeed * speedMod;
        sprite.srcRect.x = sprite.srcRect.w;
    }
    if (left)
    {
        velo.x -= shipSpeed * speedMod;
        sprite.srcRect.x = sprite.srcRect.w * 2;
    }
    if (right == left) sprite.srcRect.x = 0;
}

void PlayerControlls::boundPlayerPosition()
{
    auto& pos = playerShip.getComponent<Gng2D::Position>();

    if (pos.x < 0)                       pos.x = 0;
    if (pos.y < 0)                       pos.y = 0;
    if (pos.x > Gng2D::SCREEN_WIDTH)     pos.x = Gng2D::SCREEN_WIDTH;
    if (pos.y > Gng2D::SCREEN_HEIGHT)    pos.y = Gng2D::SCREEN_HEIGHT;
}

bool PlayerControlls::inFocusMode()
{
    return focusMode;
}

void PlayerControlls::operator()()
{
    focusMode   = scene.isKeyPressed(SDL_SCANCODE_LSHIFT);

    playerControlls();
    boundPlayerPosition();
}

