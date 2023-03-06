#include "game_over_scene.hpp"

using Gng2D::gui::Text;
using Gng2D::Coroutine;

static Coroutine fadeIn(Text& t)
{
    for (int i = 0; i <= 240; i += 2)
    {
        t.setOpacity(i);
        co_yield Coroutine::WaitTicks{1};
    }
    t.setOpacity(255);
};

void GameOverScene::onEnter()
{
    Gng2D::LOG::INFO("Entering game over scene");
    gameOverText.setScale(5);
    gameOverText.setPosition(Text::Align::Center, 0, 0);
    gameOverText.setOpacity(0);
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

void GameOverScene::render()
{
    gameOverText.render(getRenderer());
}

