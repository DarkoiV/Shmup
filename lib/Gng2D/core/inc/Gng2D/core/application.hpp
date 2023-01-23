#pragma once
#include "Gng2D/core/window.hpp"

namespace Gng2D
{
struct Application
{
    Application();

    virtual void onCreate() = 0;
    virtual void onQuit()   = 0;

    void run();
    void stopRunning();

private:
    void mainLoop();
    void eventLoop();

    Window window;

    bool running{true};
};
}

