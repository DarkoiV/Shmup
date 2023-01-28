#include "Gng2D/core/application.hpp"
#include "Gng2D/internal/window.hpp"
#include "Gng2D/internal/asset_registry.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Application::Application()
{
    Window::init("TITLE", 640, 400);
    AssetRegistry::init();
    LOG::OK("Created Gng2D application");
}

Gng2D::Application::~Application()
{
    AssetRegistry::destroy();
    Window::destroy();
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

void Gng2D::Application::setFirstScene(const std::string& name)
{
    sceneRegistry.setNextScene(name);
}

void Gng2D::Application::mainLoop()
{
    auto& scene = sceneRegistry.scene();

    eventLoop();
    scene.update();
    scene.render();

    if (scene.isCompleted()) sceneRegistry.switchScene();
}

void Gng2D::Application::eventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: 
                onQuit();
                break;
        }
    }
}

