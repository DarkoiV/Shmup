#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/acceleration.hpp"
#include "player_ship.hpp"

void FlightScene::onEnter()
{
    Gng2D::LOG::INFO("Entering flight scene");
}

void FlightScene::onExit()
{
    Gng2D::LOG::INFO("Exiting flight scene");
}

bool FlightScene::isCompleted()
{
    return false;
}

void FlightScene::update()
{
    auto& playerAcc = playerShip.getComponent<Gng2D::Acceleration>();
    playerAcc.value = {0, 0};
    if (isKeyPressed(SDL_SCANCODE_DOWN))    playerAcc.value.y += 2.0f;
    if (isKeyPressed(SDL_SCANCODE_UP))      playerAcc.value.y -= 2.0f;
    if (isKeyPressed(SDL_SCANCODE_RIGHT))   playerAcc.value.x += 2.0f;
    if (isKeyPressed(SDL_SCANCODE_LEFT))    playerAcc.value.x -= 2.0f;

    movementSystem();
}
