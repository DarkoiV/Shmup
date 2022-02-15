#include "scene_manager.hpp"
#include "log.hpp"
#include "scene.hpp"

void SceneManager::registerScene(std::string& sceneName, sceneFactory createMethod)
{
    m_registeredScenes[sceneName] = createMethod;
}

void SceneManager::nextScene(std::string& sceneName)
{
    LOG::INFO("Requestes next scene", sceneName);
    m_nextScene = m_registeredScenes[sceneName]();
}

auto SceneManager::currentScene() -> Scene*
{
    if(m_nextScene)
    {
        LOG::INFO("Switching scene");
        delete m_currentScene;
        m_currentScene = m_nextScene;
        m_nextScene = nullptr;
    }
    return m_currentScene;
}
