#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/window.hpp"

Gng2D::Application::Application()
{
    Window::init("TITLE", 640, 400);
    renderer = Window::renderer();
    LOG::OK("Created Gng2D application");
}

Gng2D::Application::~Application()
{
    assetRegistry.freeAllSprites();
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

void Gng2D::Application::mainLoop()
{
    auto& scene = sceneRegistry.getCurrentScene();

    eventLoop();
    scene.update();
    scene.render();
    renderFrame();

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

void Gng2D::Application::renderFrame()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    auto timeNow = SDL_GetTicks();
    auto expectedEnd = frameEndTime + (1000/FPS);
    if (expectedEnd > timeNow) SDL_Delay(expectedEnd - timeNow);
    frameEndTime = SDL_GetTicks();
}

