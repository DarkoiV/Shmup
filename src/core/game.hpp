#pragma once

#include "window.hpp"
#include "event_manager.hpp"

class Game 
{
    bool m_running = true;

    // Game resolution
    static constexpr int SCREEN_WIDTH  = 576;
    static constexpr int SCREEN_HEIGHT = 360;
    static inline int s_scaling = 1;

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
    EventManager eventManager = EventManager
    (
        std::bind(&Game::onQuit, this)
    );

public:
    static void loadSettings();
    void run();
};
