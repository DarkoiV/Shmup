#include <SDL2/SDL.h>
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/components/relationship.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/scene/scene.hpp"

using Gng2D::Scene;

Scene::Scene()
{
    reg.on_construct<Gng2D::NameTag>()
        .connect<&Scene::addNamedEntity>(this);
    reg.on_destroy<Gng2D::NameTag>()
        .connect<&Scene::removeNamedEntity>(this);

    reg.on_construct<Gng2D::Parent>()
        .connect<&Scene::addChildToParent>();
    reg.on_destroy<Gng2D::Parent>()
        .connect<&Scene::removeChildFromParent>();
    reg.on_destroy<Gng2D::Children>()
        .connect<&Scene::destroyAllChildren>();
    
    reg.on_update<Gng2D::Layer>()
        .connect<&Scene::updateChildrenLayer>();

    reg.ctx().emplace<Scene&>(*this);
}

Scene::~Scene()
{
    reg.on_construct<Gng2D::NameTag>()
        .disconnect<&Scene::addNamedEntity>(this);
    reg.on_destroy<Gng2D::NameTag>()
        .disconnect<&Scene::removeNamedEntity>(this);

    reg.on_construct<Gng2D::Parent>()
        .disconnect<&Scene::addChildToParent>();
    reg.on_destroy<Gng2D::Parent>()
        .disconnect<&Scene::removeChildFromParent>();
    reg.on_destroy<Gng2D::Children>()
        .disconnect<&Scene::destroyAllChildren>();

    reg.on_update<Gng2D::Layer>()
        .disconnect<&Scene::updateChildrenLayer>();
}

void Scene::onMouseMotion(SDL_MouseMotionEvent& event)
{
    mouseSystem.motion(event);
}

void Scene::operator()()
{
    if (pause) return;

    runCoroutines();
    animationSystem();
    positionSystem();
    mouseSystem();

    update();
}

bool Scene::isPaused() const
{
    return pause;
}

bool Scene::isCompleted() const 
{
    return completed;
}

bool Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

Gng2D::EntityCompositor Scene::newEntity()
{
    return EntityCompositor(reg);
}

entt::entity Scene::getEntity(const std::string& name)
{
    [[unlikely]]
    if (not namedEntities.contains(name))
    {
        Gng2D::LOG::INFO("No entity with name: \"", name, "\"");
        return entt::null;
    }
    return namedEntities[name];
}

void Scene::runCoroutines()
{
    for (auto& coro : coroutines) coro();
    std::erase_if(coroutines, [](Coroutine& coro) 
    {
        return coro.isCompleted(); 
    });
}

void Scene::addNamedEntity(entt::registry& reg, entt::entity entity)
{
    auto& name = reg.get<NameTag>(entity).value;

    [[unlikely]]
    if (namedEntities.contains(name))
    {
        Gng2D::LOG::ERROR("Entity with name: \"", name, "\" alread registered");
        reg.get<NameTag>(entity).value = "";
    }
    else
        namedEntities.emplace(name, entity);
}

void Scene::removeNamedEntity(entt::registry& reg, entt::entity entity)
{
    auto& name = reg.get<NameTag>(entity).value;
    namedEntities.erase(name);
}

void Scene::addChildToParent(entt::registry& reg, entt::entity child)
{
    auto& parentEntity = reg.get<Gng2D::Parent>(child).id;
    if (not reg.all_of<Children>(parentEntity)) reg.emplace<Children>(parentEntity);

    auto& children = reg.get<Gng2D::Children>(parentEntity).list;
    children.emplace_back(child);

    if (auto* parentLayer = reg.try_get<Gng2D::Layer>(parentEntity))
    {
        reg.emplace_or_replace<Layer>(child, 
                                      static_cast<uint8_t>(parentLayer->main), 
                                      static_cast<uint8_t>(parentLayer->sub + 1));
    }
}

void Scene::updateChildrenLayer(entt::registry& reg, entt::entity parent)
{
    auto* children = reg.try_get<Children>(parent);
    if (not children) return;

    for (const auto child : children->list)
    {
        auto parentLayer = reg.get<Layer>(parent);
        reg.emplace_or_replace<Layer>(child, 
                                      static_cast<uint8_t>(parentLayer.main), 
                                      static_cast<uint8_t>(parentLayer.sub + 1));
    }
}

void Scene::removeChildFromParent(entt::registry& reg, entt::entity child)
{
    auto& parentEntity = reg.get<Gng2D::Parent>(child).id;
    auto& children = reg.get<Gng2D::Children>(parentEntity).list;
    std::erase(children, child);
}

void Scene::destroyAllChildren(entt::registry& reg, entt::entity parent)
{
    // Copy so removeChildFromParent won't invalidate iterator
    auto children = reg.get<Gng2D::Children>(parent).list;
    for (const auto child : children)
    {
        reg.destroy(child);
    }
}

