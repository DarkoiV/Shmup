#pragma once

#include "event_manager.hpp"
#include "scene_manager.hpp"


class Scene
{
    u_int32_t eventHandlerID;

protected:
    EventManager& eventManager;
    SceneManager& sceneManager;

    virtual bool eventHandler(SDL_Event& event) = 0;

public:
    // Constructor registers default event handler for scene
    Scene(EventManager& em, SceneManager& sm): 
        eventManager(em),
        sceneManager(sm)
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
