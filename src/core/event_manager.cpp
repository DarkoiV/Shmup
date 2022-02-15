#include <algorithm>

#include "event_manager.hpp"
#include "util.hpp"
#include "log.hpp"

EventManager::EventManager(std::function<void()> onQuit)
    : quitHandler(onQuit)
{
    LOG::OK("Event manager created");
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

Uint32 EventManager::registerHandler(HandlerFn fn, int priority)
{
    m_handlers.emplace_back();
    auto& newHandler = m_handlers.back();
    newHandler.function = fn;
    newHandler.priority = priority;
    Uint32 ID = newHandler.id();

    LOG::INFO("Registering new event handler with ID:", ID);

    std::sort(m_handlers.begin(), m_handlers.end(), [](const Handler& lh, const Handler& rh)
    {
        return lh.priority < rh.priority;
    });

    return ID;
}

void EventManager::removeHandler(Uint32 ID)
{
    LOG::INFO("Removing event handler with ID:", ID);
    m_handlers.erase
    (
        std::remove_if(m_handlers.begin(), m_handlers.end(), 
        [ID](const Handler& handler)
        {
            return handler.id() == ID;
        })
    );
}
