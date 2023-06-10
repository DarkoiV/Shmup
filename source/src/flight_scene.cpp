#include "flight_scene.hpp"
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/core/application.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/systems/gui_factory.hpp"
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
            if (pause)
            {
                Gng2D::GuiFactory(reg)
                    .createText("charmap-oldschool_white",
                                "PAUSE",
                                Gng2D::Position{320, 200},
                                4)
                    .with<Gng2D::NameTag>("Pause");
            }
            else
            {
                reg.destroy(getEntity("Pause"));
            }
            break;
        case SDLK_LSHIFT:
            Gng2D::GuiFactory(reg)
                .createText("charmap-oldschool_white",
                            "FOCUS",
                            Gng2D::Position{20, 10})
                .with<Gng2D::NameTag>("Focus");
            break;
    }
}

void FlightScene::onKeyUp(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_LSHIFT:
            auto focus = getEntity("Focus");
            reg.destroy(focus);
            break;
    }
}

void FlightScene::gotoGameOver()
{
    Gng2D::Application::setNextScene<GameOverScene>();
    completed = true;
}

