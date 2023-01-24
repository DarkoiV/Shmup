#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Application::Application()
{
    LOG::OK("Created Gng2D application");
}

void Gng2D::Application::run()
{
    onCreate();
    LOG::INFO("Switching to first scene");
    sceneRegistry.switchScene();
    while (isRunning) mainLoop();
}

void Gng2D::Application::stopRunning()
{
    LOG::INFO("Application requested to stop running");
    isRunning = false;
}

void Gng2D::Application::setNextScene(const std::string& name)
{
    sceneRegistry.setNextScene(name);
}

void Gng2D::Application::mainLoop()
{
    auto& scene = sceneRegistry.scene();

    eventLoop();
    scene.update();

    if (scene.isCompleted()) sceneRegistry.switchScene();
}

void Gng2D::Application::eventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) onQuit();
    }
}

