#include "core/game.hpp"
#include "test_scene.hpp"

void Game::clientSetup()
{
    auto& sceneManager = SceneManager::get();
    sceneManager.registerScene<TestScene>("TestScene");
    sceneManager.nextScene("TestScene");
}
