#include "flight_scene.hpp"
#include "Gng2D/core/log.hpp"
#include "player_ship.hpp"

void FlightScene::onEnter()
{
    Gng2D::LOG::INFO("Entering flight scene");
    spawnObject<PlayerShip>();
}

void FlightScene::onExit()
{
    Gng2D::LOG::INFO("Exiting flight scene");
}

bool FlightScene::isCompleted()
{
    return false;
}

void FlightScene::update()
{
}
