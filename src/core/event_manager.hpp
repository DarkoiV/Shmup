#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

class EventManager
{
    // HandlerFn is function that takes SDL_Event ref
    // and returns True when event was processed
    using HandlerFn = std::function<bool(SDL_Event&)>;

    // Called on quit event
    std::function<void()> quitHandler;

    struct Handler 
    {
        HandlerFn function;
        int priority = 0;
 
        Uint32 id() const
        {
           return ID;
        }

    private:
        static inline Uint32 nextID = 0;
        Uint32 ID = nextID++;
    };

    std::vector<Handler> m_handlers;

    EventManager(std::function<void()> onQuit);
    EventManager(EventManager&)  = delete;
    EventManager(EventManager&&) = delete;

    inline static EventManager* instance = nullptr;

public:
    static void init(std::function<void()> onQuit);
    static auto get() -> EventManager&;

    // Registers handler with priority, returns ID
    Uint32 registerHandler(HandlerFn fn, int priority = 0);

    // Removes handler by ID
    void removeHandler(Uint32 ID);

    // Handle events
    void update();
};
