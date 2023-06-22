#include "main_menu_scene.hpp"
#include "Gng2D/core/application.hpp"
#include "Gng2D/types/menu_builder.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/core/log.hpp"
#include "flight_scene.hpp"

MainMenuScene::MainMenuScene()
    : menuHandle(Gng2D::MenuBuilder(reg)
            .withPosition({320.0f, 200.0f})
            .withElement("NEW GAME", [this]()
            {
                Gng2D::Application::setNextScene<FlightScene>();
                this->completed = true;
            })
            .withElement("SETTINGS", [](){})
            .withElement("QUIT", Gng2D::Application::stopRunning)
            .withBox("box", 4)
            .withMouseSupport()
            .build())
{
}

void MainMenuScene::onEnter()
{
}

void MainMenuScene::onExit()
{
}

void MainMenuScene::update()
{
    positionSystem();
}

void MainMenuScene::render(SDL_Renderer* r)
{
    entityRenderer(r);
}

void MainMenuScene::onKeyDown(SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
        case SDLK_UP:
            menuHandle.up();
            break;
        case SDLK_DOWN:
            menuHandle.down();
            break;
        case SDLK_z:
        case SDLK_RETURN:
            menuHandle.select();
            break;
    }
}

