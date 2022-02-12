#include "event_manager.hpp"
#include "util.hpp"

EventManager::EventManager(std::function<void()> onQuit)
    : quitHandler(onQuit)
{
}

void EventManager::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) quitHandler();
        else for (auto& handler : util::reverse(m_handlers))
        {
            if (handler.function(event)) break;
        }
    }
}
