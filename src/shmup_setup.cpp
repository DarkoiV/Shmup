#include "core/game.hpp"
#include "test_scene.hpp"

void Game::clientSetup()
{
    m_sceneManager.registerScene("test_scene", 
    [](EventManager& em) -> Scene*
    {
        return new TestScene(em);
    });
    m_sceneManager.nextScene("test_scene");
}
