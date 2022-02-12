#pragma once

#include "window.hpp"

class Game 
{
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

public:
    static void loadSettings();
    void run();
};
