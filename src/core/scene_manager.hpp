#pragma once

#include <memory>
#include <functional>
#include <map>
#include <string_view>

#include "log.hpp"

class Scene;
class EventManager;

class SceneManager
{
    // Scene dependencies
    friend Scene;
    EventManager& eventManager;

    // Scene factory is function that creates scene of conrete type
    using sceneFactory = std::function<Scene*(SceneManager&)>;

    // All registered scenes
    std::map<std::string, sceneFactory> m_registeredScenes;

    Scene* m_currentScene = nullptr;
    Scene* m_nextScene    = nullptr;

    template<class T>
    auto createSceneFactory() -> sceneFactory
    {
        return [](SceneManager& sm){ return new T(sm); };
    }

public:
    SceneManager(EventManager& em);
    ~SceneManager();

    template<class T>
    void registerScene(const std::string& name)
    {
        LOG::INFO("Registering new scene type", name);
        m_registeredScenes[name] = createSceneFactory<T>();
    }

    void nextScene(const std::string& name);

    auto currentScene() -> Scene*;
};
