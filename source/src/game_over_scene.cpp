#include "game_over_scene.hpp"

void GameOverScene::onEnter()
{
    Gng2D::LOG::INFO("Entering game over scene");
}

void GameOverScene::onExit()
{
    Gng2D::LOG::INFO("Exiting game over scene");
}

bool GameOverScene::isCompleted()
{
    return false;
}

void GameOverScene::update()
{
}

void GameOverScene::render(SDL_Renderer*)
{
}

