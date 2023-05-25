#include "flight_scene.hpp"
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "components/hit_points.hpp"
#include "game_over_scene.hpp"
#include "levels.hpp"

FlightScene::FlightScene()
{
    addCoroutine(levelOne, *this, entityFactory);
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
    if (playerControlls.isPlayerAlive())
    {
        sceneRegistry.setNextScene<GameOverScene>();
        return true;
    }
    return false;
}

void FlightScene::update()
{
    playerControlls();
    enemyBulletSpawner();
    movement();
    animatonSystem();
    collisionSystem();
    entityCleaner();
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
            auto focus = guiSystem.createText("charmap-oldschool_white",
                                             "FOCUS",
                                             Gng2D::Position{20, 10});
            enttRegistry.emplace<Gng2D::NameTag>(focus, "Focus");
            break;
    }
}

void FlightScene::onKeyUp(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_LSHIFT:
            auto focus = getEntity("Focus");
            enttRegistry.destroy(focus);
            break;
    }
}

