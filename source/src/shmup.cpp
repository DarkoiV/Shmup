#include "shmup.hpp"
#include "flight_scene.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/scene_registry.hpp"

void Shmup::onCreate()
{
    Gng2D::LOG::INFO("Creating Shmup");
    sceneRegistry.setNextScene<FlightScene>();
    assetRegistry.loadSprite("data/Clojure.png");
}

void Shmup::onQuit()
{
    stopRunning();
}
