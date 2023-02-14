#pragma once
#include "Gng2D/types/scene.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/asset_registry.hpp"

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

protected:
    AssetRegistry   assetRegistry;
    SceneRegistry   sceneRegistry;

private:
    void mainLoop();
    void eventLoop();

    bool    isRunning{true};
    Window  window;
};
}

