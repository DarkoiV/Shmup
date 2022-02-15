#pragma once

#include "event_manager.hpp"

class Scene
{
    u_int32_t eventHandlerID;
    EventManager& eventManager;

protected:
    virtual bool eventHandler(SDL_Event& event) = 0;

public:
    // Constructor registers default event handler for scene
    Scene(EventManager& em)
        : eventManager(em)
    {
        eventHandlerID = eventManager.registerHandler(std::bind
        (
            &Scene::eventHandler,
            this,
            std::placeholders::_1
        ));
    }

    // Destructor removes scene event handler
    virtual ~Scene()
    {
        eventManager.removeHandler(eventHandlerID);
    }

    virtual void update() = 0;
    virtual bool completed() = 0;
};
