#include "game_over_scene.hpp"
#include "Gng2D/core/log.hpp"

void GameOverScene::onEnter()
{
    Gng2D::LOG::INFO("Entering game over scene");
}

void GameOverScene::onExit()
{
    Gng2D::LOG::INFO("Exiting game over scene");
}

void GameOverScene::update()
{
}

void GameOverScene::render(SDL_Renderer*)
{
}

