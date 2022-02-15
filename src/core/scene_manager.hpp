#pragma once

#include <memory>
#include <functional>
#include <map>
#include <string_view>

class Scene;
class EventManager;

class SceneManager
{
    EventManager& eventManager;

    // Scene factory is function that creates scene of conrete type
    using sceneFactory = std::function<Scene*(EventManager&, SceneManager&)>;

    // All registered scenes
    std::map<std::string, sceneFactory> m_registeredScenes;

    Scene* m_currentScene = nullptr;
    Scene* m_nextScene    = nullptr;

public:
    SceneManager(EventManager& em);
    ~SceneManager();

    void registerScene(const std::string& sceneName, sceneFactory createMethod);
    void nextScene(const std::string& sceneName);

    auto currentScene() -> Scene*;
};
