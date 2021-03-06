#include "game.hpp"
#include "log.hpp"
#include "scene.hpp"

#include <fstream>

Game::Game()
{
    EventManager::init
    (
        std::bind(&Game::onQuit, this)
    );

    SceneManager::init();

    Window::init(WINDOW_WIDTH, WINDOW_HEIGHT, s_scaling);
}

void Game::onQuit()
{
    LOG::INFO("Requested quitting");
    m_running = false;
}

void Game::loadSettings() 
{
    s_gameDirectory = SDL_GetBasePath();
    LOG::INFO("Game running in", s_gameDirectory);

    s_dataFolder = s_gameDirectory + "data/";
    LOG::INFO("Looking for data in", s_dataFolder);

    std::string settingsPath = s_dataFolder + "settings.txt";
    LOG::INFO("Opening settings file:", settingsPath);
    std::ifstream settingsFile(settingsPath);

    if (not settingsFile.is_open()) LOG::FATAL("Couldn't open settings file");

    // Load settings from file
    std::string setting, value;
    while(settingsFile >> setting >> value)
    {
        LOG::INFO("Setting", setting, "to", value);
        if(setting == "scale")
        {
            s_scaling = std::stoi(value);
            continue;
        }
        
        LOG::WARN("Unknown setting", setting);
    }

    LOG::OK("Loaded all settings!\n");
}

void Game::run() 
{
    LOG::INFO("Client setup");
    clientSetup();

    auto& sceneManager = SceneManager::get();
    auto& eventManager = EventManager::get();
    auto& window = Window::get();

    LOG::INFO("Starting game loop \n");
    while (m_running)
    {
        auto scene = sceneManager.currentScene();
        while (not scene->completed() and m_running)
        {
            eventManager.update();
            scene->update();
            window.update();
        }
    }
}
