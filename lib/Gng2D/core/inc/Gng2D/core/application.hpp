#pragma once
#include "Gng2D/core/window.hpp"

namespace Gng2D
{
struct Application
{
    Application();

    virtual void onCreate() = 0;

    void run();

private:
    Window window;
};
}

