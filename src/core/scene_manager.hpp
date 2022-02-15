#pragma once

#include <memory>
#include <functional>
#include <map>
#include <string_view>

class Scene;

class SceneManager
{
    // Scene factory is function that creates scene of conrete type
    using sceneFactory = std::function<Scene*()>;

    // All registered scenes
    std::map<std::string, sceneFactory> m_registeredScenes;

    Scene* m_currentScene = nullptr;
    Scene* m_nextScene    = nullptr;
public:

    void registerScene(std::string& sceneName, sceneFactory createMethod);
    void nextScene(std::string& sceneName);

    auto currentScene() -> Scene*;
};
