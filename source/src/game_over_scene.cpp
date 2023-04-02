#include "game_over_scene.hpp"
#include "Gng2D/gui/text_animations.hpp"

using Gng2D::gui::Text;
using Gng2D::gui::fadeIn;

void GameOverScene::onEnter()
{
    Gng2D::LOG::INFO("Entering game over scene");
    gameOverText.setScale(5);
    gameOverText.setPosition(Text::Align::Center, 0, 0);
    gameOverText.setOpacity(0);
    gameOverText.setColorMod(255, 35, 25);
    addCoroutine(fadeIn, gameOverText);
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

void GameOverScene::render(SDL_Renderer* r)
{
    gameOverText.render(r);
}

