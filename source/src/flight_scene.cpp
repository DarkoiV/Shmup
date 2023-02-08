#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/components/acceleration.hpp"

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
    static int spawnCounter;
    if (spawnCounter == 60)
    {
        spawnObject<Bullet>();
        spawnCounter = 0;
    }
    spawnCounter++;

    auto& playerAcc = playerShip.getComponent<Gng2D::Acceleration>();
    playerAcc = {0, 0};
    float speedMod = 1.0f;
    if (isKeyPressed(SDL_SCANCODE_LSHIFT))  speedMod = 0.25f;
    if (isKeyPressed(SDL_SCANCODE_DOWN))    playerAcc.y += 2.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_UP))      playerAcc.y -= 2.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_RIGHT))   playerAcc.x += 2.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_LEFT))    playerAcc.x -= 2.0f * speedMod;

    movementSystem();
    playerBulletCollisionSystem();
}

void FlightScene::render()
{
    Gng2D::Scene::render();
    playerColliderRenderer();
    bulletColliderRenderer();
}

