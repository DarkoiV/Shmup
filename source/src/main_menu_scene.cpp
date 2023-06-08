#include "main_menu_scene.hpp"
#include "Gng2D/types/menu_builder.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/core/log.hpp"

void MainMenuScene::onEnter()
{
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
        .withBox("box")
        .withElement("NEW GAME", [](){})
        .withElement("SETTINGS", [](){})
        .withElement("QUIT", [](){})
        .build();
}

void MainMenuScene::onExit()
{
}

bool MainMenuScene::isCompleted()
{
    return false;
}

void MainMenuScene::update()
{
    positionSystem();
}

void MainMenuScene::render(SDL_Renderer* r)
{
    entityRenderer(r);
}

