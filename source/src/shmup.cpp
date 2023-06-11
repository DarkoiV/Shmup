#include "shmup.hpp"
#include "flight_scene.hpp"
#include "main_menu_scene.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/scene/gui_system.hpp"

void Shmup::onCreate()
{
    Gng2D::LOG::INFO("Creating Shmup");
    assetRegistry.loadSprite("player_ship");
    assetRegistry.loadSprite("ally_bullet");
    assetRegistry.loadSprite("enemy_bullet");
    assetRegistry.loadSprite("hitpoints");
    assetRegistry.loadSprite("sparrow");
    assetRegistry.loadSprite("red_x");
    assetRegistry.loadSprite("pickup");
    assetRegistry.loadSprite("drone");
    assetRegistry.loadSprite("box");
    assetRegistry.loadSprite("turret");
    assetRegistry.loadSprite("turret_boat");
    assetRegistry.loadBMFont("charmap-oldschool_white", 7, 9);
    assetRegistry.loadBMFont("charmap-oldschool_black", 7, 9);

    Gng2D::GuiSystem::defaultFont                   = "charmap-oldschool_white";
    Gng2D::GuiSystem::defaultBoxTiles               = "box";
    Gng2D::GuiSystem::defaultOnHighlightFunc        = [](auto& text)
    {
        text.changeRGBMod(120, 255, 155);
    };
    Gng2D::GuiSystem::defaultOnStopHighlightFunc    = [](auto& text)
    {
        text.changeRGBMod(255, 255, 255);
    };

    setNextScene<MainMenuScene>();
}

void Shmup::onQuit()
{
    stopRunning();
    if (currentScene)
        currentScene->onExit();
}

