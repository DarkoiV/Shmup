#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/settings.hpp"

Gng2D::Application::Application()
{
    AssetRegistry::renderer     = window.renderer();
    LOG::OK("Created Gng2D application");
}

Gng2D::Application::~Application()
{
    assetRegistry.freeAllSprites();
}

void Gng2D::Application::run()
{
    onCreate();
    LOG::INFO("Switching to first scene");
    switchScene();
    while (isRunning) mainLoop();
}

void Gng2D::Application::stopRunning()
{
    LOG::INFO("Application requested to stop running");
    isRunning = false;
}

void Gng2D::Application::mainLoop()
{
    auto& scene = sceneRegistry.getCurrentScene();
    uint64_t currentTS  = SDL_GetTicks64();
    uint32_t elapsed    = currentTS - previousTS;
    previousTS          = currentTS;
    logicLag           += elapsed;

    eventLoop();
    while (logicLag >= LOGIC_TICK)
    {
        scene();
        logicLag -= LOGIC_TICK;
    }
    scene.render(window.renderer());
    window.renderFrame();
    window.displayFPS();

    if (scene.isCompleted()) switchScene(); 
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

void Gng2D::Application::switchScene()
{
    sceneRegistry.switchScene();
    previousTS  = SDL_GetTicks();
    logicLag    = 0;
}

