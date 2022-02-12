#include <algorithm>

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

int EventManager::registerHandler(HandlerFn fn, int priority)
{
    m_handlers.emplace_back();
    auto& newHandler = m_handlers.back();
    newHandler.function = fn;
    newHandler.priority = priority;

    std::sort(m_handlers.begin(), m_handlers.end(), [](const Handler& lh, const Handler& rh)
    {
        return lh.priority < rh.priority;
    });

    return newHandler.id();
}

void EventManager::removeHandler(int ID)
{
    m_handlers.erase
    (
        std::remove_if(m_handlers.begin(), m_handlers.end(), 
        [ID](const Handler& handler)
        {
            return handler.id() == ID;
        })
    );
}
