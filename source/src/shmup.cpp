#include "shmup.hpp"
#include "flight_scene.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/scene_registry.hpp"

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
    sceneRegistry.setNextScene<FlightScene>();
}

void Shmup::onQuit()
{
    stopRunning();
    auto& scene = sceneRegistry.getCurrentScene();
    scene.onExit();
}

