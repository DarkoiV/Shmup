#include "main_menu_scene.hpp"
#include "Gng2D/core/application.hpp"
#include "Gng2D/types/menu_builder.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/core/log.hpp"
#include "flight_scene.hpp"

void MainMenuScene::onEnter()
{
    auto gotoNewGame = [this]()
    {
        Gng2D::Application::setNextScene<FlightScene>();
        this->completed = true;
    };
    menu = Gng2D::MenuBuilder(reg)
        .withPosition({320.0f, 200.0f})
        .withFont("charmap-oldschool_white")
        .withOnHighlightFunc([&](auto& text)
        {
            text.changeRGBMod(120, 255, 155);
        })
        .withOnStopHighlightFunc([](auto& text)
        {
            text.changeRGBMod(255, 255, 255);
        })
        .withBox("box", 1)
        .withElement("NEW GAME", gotoNewGame)
        .withElement("SETTINGS", [](){})
        .withElement("QUIT", Gng2D::Application::stopRunning)
        .build();

    guiSystem.makeActiveMenu(menu);
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
            guiSystem.activeMenuUp();
            break;
        case SDLK_DOWN:
            guiSystem.activeMenuDown();
            break;
        case SDLK_RETURN:
            guiSystem.activeMenuSelect();
            break;
    }
}

