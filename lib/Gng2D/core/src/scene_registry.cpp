#include "Gng2D/components/scene.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Scene& Gng2D::SceneRegistry::getCurrentScene() const
{
    return *currentScene;
}

void Gng2D::SceneRegistry::switchScene()
{
    if (not nextScene) LOG::ERROR("No next scene set, cannot switch");
    else
    {
        if (currentScene) currentScene->onExit();
        currentScene = std::move(nextScene);
        currentScene->onEnter();
    }

    if (not currentScene) LOG::FATAL("No current scene after switching!");
}
