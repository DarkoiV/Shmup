#pragma once
#include "Gng2D/core/window.hpp"
#include "Gng2D/components/scene.hpp"
#include "Gng2D/core/scene_registry.hpp"

namespace Gng2D
{
struct Application
{
    Application();

    virtual void onCreate() = 0;
    virtual void onQuit()   = 0;

    void run();
    void stopRunning();
    void setNextScene(const std::string& name);

private:
    void mainLoop();
    void eventLoop();

    Window          window;
    SceneRegistry   sceneRegistry;

    bool isRunning{true};
};
}
