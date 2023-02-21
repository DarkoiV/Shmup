#include "shmup.hpp"
#include "flight_scene.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/scene_registry.hpp"

void Shmup::onCreate()
{
    Gng2D::LOG::INFO("Creating Shmup");
    assetRegistry.loadSprite("player_ship");
    sceneRegistry.setNextScene<FlightScene>();
}

void Shmup::onQuit()
{
    auto& scene = sceneRegistry.getCurrentScene();
    scene.onExit();
    stopRunning();
}
