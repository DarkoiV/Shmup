#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/log.hpp"

auto Gng2D::SceneRegistry::scene() -> Scene&
{
    return *currentScene;
}

void Gng2D::SceneRegistry::setNextScene(const std::string& name)
{
    LOG::INFO("Setting next scene to:", name);

    if (not registered.contains(name)) LOG::ERROR("No registered scene named: ", name);
    else nextScene = registered.at(name)();
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
