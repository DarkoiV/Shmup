#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/settings.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/gui/text.hpp"
#include "levels.hpp"

FlightScene::FlightScene()
{
    addCoroutine(levelOne, *this);
}

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
    playerControlls();
    movement();
    boundPlayerPosition();

    playerWeapons();
    playerBulletCollision();
    bulletBulletCollision();

    entityCleaner();
}

void FlightScene::render()
{
    Gng2D::Scene::render();
    playerColliderRenderer();
    allyBulletColliderRenderer();
    enemyBulletColliderRenderer();
    Gng2D::gui::Text t("charmap-oldschool_white", "Hello!");
    t.render(getRenderer(), 20, 20);
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
    if (playerPosition.x < 0)                       playerPosition.x = 0;
    if (playerPosition.y < 0)                       playerPosition.y = 0;
    if (playerPosition.x > Gng2D::SCREEN_WIDTH)     playerPosition.x = Gng2D::SCREEN_WIDTH;
    if (playerPosition.y > Gng2D::SCREEN_HEIGHT)    playerPosition.y = Gng2D::SCREEN_HEIGHT;
}

