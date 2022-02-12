#include "game.hpp"
#include "log.hpp"

void Game::onQuit()
{
    LOG::INFO("Requested quitting");
    m_running = false;
}

void Game::loadSettings() 
{
    // Load game settings here
}

void Game::run() 
{
    while (m_running)
    {
        m_eventManager.update();
        m_window.update();
    }
}
