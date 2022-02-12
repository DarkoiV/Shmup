#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

class EventManager
{
    // Event HandlerFn is function that takes SDL_Event
    // and returns True when event was processed
    using HandlerFn = std::function<bool(SDL_Event&)>;

    // Called on quit event
    std::function<void()> quitHandler;

    struct Handler 
    {
        HandlerFn function;
        int priority = 0;

        Handler()
        {
            ID = nextID;
            nextID++;
        }
        
        int id() const
        {
           return ID;
        }

    private:
        static inline int nextID = 0;
        int ID;
    };

    std::vector<Handler> m_handlers;

public:
    EventManager(std::function<void()> onQuit);
    EventManager(EventManager&)  = delete;
    EventManager(EventManager&&) = delete;

    // Registers handler with priority, returns ID
    int registerHandler(HandlerFn fn, int priority = 0);

    // Removes handler by ID
    void removeHandler(int ID);

    // Handle events
    void update();
};
