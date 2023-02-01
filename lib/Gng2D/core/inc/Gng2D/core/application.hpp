#pragma once
#include "Gng2D/components/scene.hpp"
#include "Gng2D/core/scene_registry.hpp"

namespace Gng2D
{
struct Application
{
    Application();
    virtual ~Application();

    virtual void onCreate() = 0;
    virtual void onQuit()   = 0;

    void run();
    void stopRunning();

private:
    void mainLoop();
    void eventLoop();

    bool isRunning{true};
};
}

