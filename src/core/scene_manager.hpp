#pragma once

#include <memory>
#include <functional>
#include <map>
#include <string_view>

#include "log.hpp"

class Scene;

class SceneManager
{
    // Scene factory is function that creates scene of conrete type
    using sceneFactory = std::function<Scene*()>;

    // All registered scenes
    std::map<std::string, sceneFactory> m_registeredScenes;

    Scene* m_currentScene = nullptr;
    Scene* m_nextScene    = nullptr;

    template<class T>
    auto createSceneFactory() -> sceneFactory
    {
        return [](){ return new T(); };
    }

    SceneManager() = default;
    SceneManager(SceneManager&)  = delete;
    SceneManager(SceneManager&&) = delete;
    ~SceneManager();

    inline static SceneManager* instance = nullptr;

public:
    static void init();
    static auto get() -> SceneManager&;

    template<class T>
    void registerScene(const std::string& name)
    {
        LOG::INFO("Registering new scene type", name);
        m_registeredScenes[name] = createSceneFactory<T>();
    }

    void nextScene(const std::string& name);

    auto currentScene() -> Scene*;
};
