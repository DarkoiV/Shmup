#pragma once

#include <functional>

#include <SDL2/SDL.h>
#include <vector>

class EventManager
{
public:
    // Event handler is function that takes SDL_Event
    // and returns True when event was processed
    using HandlerFn = std::function<bool(SDL_Event&)>;

private:
    // Called on quit event
    std::function<void()> quitHandler;

    struct Handler {
        HandlerFn function;
        int priority;
        const int ID;

        Handler()
            : ID(nextID)
        {
            nextID++;
        }

    private:
        static int nextID;
    };

    std::vector<Handler> m_handlers;

public:
    EventManager(std::function<void()> onQuit);
    EventManager(EventManager&)  = delete;
    EventManager(EventManager&&) = delete;

    void update();
};
