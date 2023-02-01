#include "Gng2D/core/application.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/internal/window.hpp"

Gng2D::Application::Application()
{
    Window::init("TITLE", 640, 400);
    LOG::OK("Created Gng2D application");
}

Gng2D::Application::~Application()
{
    AssetRegistry::freeAllSprites();
    Window::destroy();
}

void Gng2D::Application::run()
{
    onCreate();
    LOG::INFO("Switching to first scene");
    SceneRegistry::switchScene();
    while (isRunning) mainLoop();
}

void Gng2D::Application::stopRunning()
{
    LOG::INFO("Application requested to stop running");
    isRunning = false;
}

void Gng2D::Application::mainLoop()
{
    auto& scene = SceneRegistry::scene();

    eventLoop();
    scene.update();
    scene.render();

    if (scene.isCompleted()) SceneRegistry::switchScene();
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

