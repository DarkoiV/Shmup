#include "systems/player_controlls.hpp"
#include "Gng2D/core/settings.hpp"

void PlayerControlls::playerControlls()
{
    auto& playerVelocity = playerShip.getComponent<Gng2D::Velocity>();
    playerVelocity = {0, 0};

    bool focusMode = scene.isKeyPressed(SDL_SCANCODE_LSHIFT);
    float speedMod = focusMode ? 0.3f : 1.0f;

    if (scene.isKeyPressed(SDL_SCANCODE_DOWN))    playerVelocity.y += 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_UP))      playerVelocity.y -= 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_RIGHT))   playerVelocity.x += 4.0f * speedMod;
    if (scene.isKeyPressed(SDL_SCANCODE_LEFT))    playerVelocity.x -= 4.0f * speedMod;
}

void PlayerControlls::boundPlayerPosition()
{
    auto& playerPosition = playerShip.getComponent<Gng2D::Position>();
    if (playerPosition.x < 0)                       playerPosition.x = 0;
    if (playerPosition.y < 0)                       playerPosition.y = 0;
    if (playerPosition.x > Gng2D::SCREEN_WIDTH)     playerPosition.x = Gng2D::SCREEN_WIDTH;
    if (playerPosition.y > Gng2D::SCREEN_HEIGHT)    playerPosition.y = Gng2D::SCREEN_HEIGHT;
}

void PlayerControlls::operator()()
{
    playerControlls();
    boundPlayerPosition();
}

