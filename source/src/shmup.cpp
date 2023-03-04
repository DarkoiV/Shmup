#include "shmup.hpp"
#include "flight_scene.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/scene_registry.hpp"

void Shmup::onCreate()
{
    Gng2D::LOG::INFO("Creating Shmup");
    assetRegistry.loadSprite("player_ship");
    assetRegistry.loadBMFont("charmap-oldschool_white", 7, 9);
    sceneRegistry.setNextScene<FlightScene>();
}

void Shmup::onQuit()
{
    stopRunning();
    auto& scene = sceneRegistry.getCurrentScene();
    scene.onExit();
}
