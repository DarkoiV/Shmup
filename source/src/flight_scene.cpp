#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/gui/text.hpp"
#include "game_over_scene.hpp"
#include "levels.hpp"

FlightScene::FlightScene()
{
    addCoroutine(levelOne, *this, flightSceneGui);
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
    if (const auto& hp = playerShip.getComponent<HitPoints>(); hp.value <= 0)
    {
        sceneRegistry.setNextScene<GameOverScene>();
        return true;
    }
    return false;
}

void FlightScene::update()
{
    movement();

    playerControlls();
    enemyBulletSpawner();

    playerBulletCollision();
    bulletBulletCollision();
    bulletEnemyCollision();
    playerEnemyCollision();

    animationSystem();
    entityCleaner();

    flightSceneGui();
}

void FlightScene::render(SDL_Renderer* r)
{
    entityRenderer(r);
    if (playerControlls.inFocusMode()) playerColliderRenderer(r);
    flightSceneGui.render(r);
}

void FlightScene::onKeyDown(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_p:
            pause = !pause;
            break;
    }
}

