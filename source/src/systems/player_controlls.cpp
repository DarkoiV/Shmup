#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"

void PlayerControlls::playerControlls()
{
    auto& velo  = playerShip.getComponent<Gng2D::Velocity>();
    velo        = {0, 0};
    float speedMod = focusMode ? 0.3f : 1.0f;

    if (scene.isKeyPressed(SDL_SCANCODE_DOWN))    velo.y += 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_UP))      velo.y -= 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_RIGHT))   velo.x += 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_LEFT))    velo.x -= 4.0f * speedMod;
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

