#include "scene_manager.hpp"
#include "log.hpp"
#include "scene.hpp"

SceneManager::SceneManager(EventManager& em)
    : eventManager(em)
{
}

SceneManager::~SceneManager()
{
    if (m_nextScene) delete m_nextScene;
    delete m_currentScene;
}

void SceneManager::registerScene(const std::string& sceneName, sceneFactory createMethod)
{
    LOG::INFO("Registering new scene type", sceneName);
    m_registeredScenes[sceneName] = createMethod;
}

void SceneManager::nextScene(const std::string& sceneName)
{
    LOG::INFO("Requestes next scene", sceneName);
    m_nextScene = m_registeredScenes[sceneName](*this);
}

auto SceneManager::currentScene() -> Scene*
{
    if (m_nextScene)
    {
        LOG::INFO("Switching scene");
        delete m_currentScene;
        m_currentScene = m_nextScene;
        m_nextScene = nullptr;
    }

    if (not m_currentScene) LOG::FATAL("No current scene loaded");
    return m_currentScene;
}
