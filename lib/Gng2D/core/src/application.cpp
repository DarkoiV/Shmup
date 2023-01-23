#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Application::Application()
{
    LOG::OK("Created Gng2D application");
}

void Gng2D::Application::run()
{
    onCreate();
    while (running) mainLoop();
}

void Gng2D::Application::stopRunning()
{
    LOG::INFO("Application requested to stop running");
    running = false;
}

void Gng2D::Application::mainLoop()
{
    eventLoop();
}

void Gng2D::Application::eventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) onQuit();
    }
}

