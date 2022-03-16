#pragma once

#include "event_manager.hpp"
#include "scene_manager.hpp"


class Scene
{
    u_int32_t eventHandlerID;

protected:
    SceneManager& sceneManager;
    EventManager& eventManager;

    virtual bool eventHandler(SDL_Event& event) = 0;

public:
    // Constructor registers default event handler for scene
    Scene(): 
        sceneManager(SceneManager::get()),
        eventManager(EventManager::get())
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
