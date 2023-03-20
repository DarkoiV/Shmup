#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/gui/text.hpp"
#include "game_over_scene.hpp"
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
    playerWeapons();

    playerBulletCollision();
    bulletBulletCollision();

    const auto& [HP, maxHP] = playerShip.getComponent<HitPoints>();
    flightSceneGui.setHP(HP, maxHP);

    entityCleaner();
}

void FlightScene::render(SDL_Renderer* r)
{
    entityRenderer(r);
    if (playerControlls.inFocusMode()) 
    {
        playerColliderRenderer(r);
        flightSceneGui.renderFocusMode(r);
    }
    flightSceneGui.renderHitPoints(r);
}

