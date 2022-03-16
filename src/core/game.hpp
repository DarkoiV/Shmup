#pragma once

#include "window.hpp"
#include "event_manager.hpp"
#include "scene_manager.hpp"

#include <string>

class Game 
{
    bool m_running = true;

    static inline std::string s_gameDirectory;
    static inline std::string s_dataFolder;

    // Game settings
    static constexpr int WINDOW_WIDTH  = 576;
    static constexpr int WINDOW_HEIGHT = 360;
    static inline int s_scaling = 2;
 
    // Handle requst for quitting
    void onQuit();

public:
    static void loadSettings();

    Game();
    void clientSetup();
    void run();
};
