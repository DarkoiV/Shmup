#include "flight_scene.hpp"
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/core/application.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "components/hit_points.hpp"
#include "game_over_scene.hpp"
#include "levels.hpp"

FlightScene::FlightScene()
{
    addCoroutine(levelOne, reg);
}

void FlightScene::onEnter()
{
    Gng2D::LOG::INFO("Entering flight scene");
}

void FlightScene::onExit()
{
    Gng2D::LOG::INFO("Exiting flight scene");
}

void FlightScene::update()
{
    playerControlls();
    enemyWeapons();
    collisionSystem();
    entityCleaner();

    if (not playerControlls.isPlayerAlive()) gotoGameOver();
}

void FlightScene::render(SDL_Renderer* r)
{
    entityRenderer(r);
    if (playerControlls.inFocusMode()) playerColliderRenderer(r);
}


void FlightScene::onKeyDown(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_p:
            pause = !pause;
            break;
        case SDLK_LSHIFT:
            break;
    }
}

void FlightScene::onKeyUp(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_LSHIFT:
            break;
    }
}

void FlightScene::gotoGameOver()
{
    Gng2D::Application::setNextScene<GameOverScene>();
    completed = true;
}

