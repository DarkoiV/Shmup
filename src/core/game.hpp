#pragma once

#include "window.hpp"
#include "event_manager.hpp"

#include <string>

class Game 
{
    bool m_running = true;

    static inline std::string s_gameDirectory;
    static inline std::string s_dataFolder;

    // Game resolution
    static constexpr int SCREEN_WIDTH  = 576;
    static constexpr int SCREEN_HEIGHT = 360;
    static inline int s_scaling = 2;

    // Game window
    Window m_window = Window
    (
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        s_scaling
    );
 
    // Handle requst for quitting
    void onQuit();

    // Event manager
    EventManager m_eventManager = EventManager
    (
        std::bind(&Game::onQuit, this)
    );

public:
    static void loadSettings();
    void run();
};
