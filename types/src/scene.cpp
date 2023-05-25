#include <SDL2/SDL.h>
#include "Gng2D/components/name_tag.hpp"
#include "Gng2D/components/relationship.hpp"
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/core/window.hpp"
#include "Gng2D/types/scene.hpp"

using Gng2D::Scene;

Scene::Scene()
{
    enttRegistry
        .on_construct<Gng2D::NameTag>()
        .connect<&Scene::addNamedEntity>(this);
    enttRegistry
        .on_destroy<Gng2D::NameTag>()
        .connect<&Scene::removeNamedEntity>(this);

    enttRegistry
        .on_construct<Gng2D::Child>()
        .connect<&Scene::addChildToParent>();
    enttRegistry
        .on_destroy<Gng2D::Child>()
        .connect<&Scene::removeChildFromParent>();
    enttRegistry
        .on_destroy<Gng2D::Parent>()
        .connect<&Scene::destroyAllChildren>();
}

Scene::~Scene()
{
    enttRegistry
        .on_construct<Gng2D::NameTag>()
        .disconnect<&Scene::addNamedEntity>(this);
    enttRegistry
        .on_destroy<Gng2D::NameTag>()
        .disconnect<&Scene::removeNamedEntity>(this);

    enttRegistry
        .on_construct<Gng2D::Child>()
        .disconnect<&Scene::addChildToParent>();
    enttRegistry
        .on_destroy<Gng2D::Child>()
        .disconnect<&Scene::removeChildFromParent>();
    enttRegistry
        .on_destroy<Gng2D::Parent>()
        .disconnect<&Scene::destroyAllChildren>();
}

void Scene::operator()()
{
    if (pause) return;

    runCoroutines();
    update();
}

bool Scene::isPaused() const
{
    return pause;
}

bool Scene::isKeyPressed(SDL_Scancode scancode) const
{
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[scancode];
}

Gng2D::EntityBuilder Scene::newEntity()
{
    return EntityBuilder(enttRegistry);
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
    auto& parentEntity = reg.get<Gng2D::Child>(child).parent;
    if (not reg.all_of<Parent>(parentEntity)) reg.emplace<Parent>(parentEntity);

    auto& children = reg.get<Gng2D::Parent>(parentEntity).children;
    children.emplace_back(child);
}

void Scene::removeChildFromParent(entt::registry& reg, entt::entity child)
{
    auto& parentEntity = reg.get<Gng2D::Child>(child).parent;
    auto& children = reg.get<Gng2D::Parent>(parentEntity).children;
    std::erase(children, child);
}

void Scene::destroyAllChildren(entt::registry& reg, entt::entity parent)
{
    auto& children = reg.get<Gng2D::Parent>(parent).children;
    for (const auto child : children)
    {
        reg.destroy(child);
    }
}

