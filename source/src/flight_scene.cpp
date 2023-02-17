#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/settings.hpp"

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
    if (const auto& stats = playerShip.getComponent<Stats>(); stats.health <= 0)
    {
        // TODO switch to GameOver scene
        return true;
    }
    return false;
}

void FlightScene::update()
{
    static int spawnCounter;
    if (spawnCounter == 20)
    {
        spawnObject<EnemyBullet>(Gng2D::Position{320.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
        spawnObject<EnemyBullet>(Gng2D::Position{120.0f, 0.0f}, Gng2D::Velocity{1.41f, 1.41f});
    }
    if (spawnCounter == 40)
    {
        spawnObject<EnemyBullet>(Gng2D::Position{400.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
    }
    if (spawnCounter == 60)
    {
        spawnObject<EnemyBullet>(Gng2D::Position{240.0f, 0.0f}, Gng2D::Velocity{0.0f, 2.0f});
        spawnObject<EnemyBullet>(Gng2D::Position{520.0f, 0.0f}, Gng2D::Velocity{-1.41f, 1.41f});
        spawnCounter = 0;
    }
    spawnCounter++;

    playerControlls();
    movement();
    boundPlayerPosition();

    playerWeapons();
    playerBulletCollision();
    bulletBulletCollision();
}

void FlightScene::render(uint32_t msLag)
{
    Gng2D::Scene::render(msLag);
    playerColliderRenderer(msLag);
    allyBulletColliderRenderer(msLag);
    enemyBulletColliderRenderer(msLag);
}

void FlightScene::playerControlls()
{
    auto& playerVelocity = playerShip.getComponent<Gng2D::Velocity>();
    playerVelocity = {0, 0};
    float speedMod = 1.0f;
    if (isKeyPressed(SDL_SCANCODE_LSHIFT))  speedMod = 0.25f;
    if (isKeyPressed(SDL_SCANCODE_DOWN))    playerVelocity.y += 4.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_UP))      playerVelocity.y -= 4.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_RIGHT))   playerVelocity.x += 4.0f * speedMod;
    if (isKeyPressed(SDL_SCANCODE_LEFT))    playerVelocity.x -= 4.0f * speedMod;

    if (isKeyPressed(SDL_SCANCODE_Z))       playerWeapons.primaryFire();
}

void FlightScene::boundPlayerPosition()
{
    auto& playerPosition = playerShip.getComponent<Gng2D::Position>();
    const float maxX = Gng2D::SCREEN_WIDTH;
    const float maxY = Gng2D::SCREEN_HEIGHT;
    playerPosition.bound({0,0}, Gng2D::V2d{maxX, maxY});
}

