#include "core/game.hpp"
#include "test_scene.hpp"

void Game::clientSetup()
{
    m_sceneManager.registerScene<TestScene>("TestScene");
    m_sceneManager.nextScene("TestScene");
}
