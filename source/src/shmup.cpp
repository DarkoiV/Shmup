#include "shmup.hpp"
#include "flight_scene.hpp"

void Shmup::onCreate()
{
    Gng2D::LOG::INFO("Creating Shmup");
    GNG2D_REGISTER_SCENE(FlightScene);
    setFirstScene("FlightScene");
}

void Shmup::onQuit()
{
    stopRunning();
}
