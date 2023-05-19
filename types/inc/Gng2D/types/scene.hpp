#pragma once
#include <memory>
#include <vector>
#include <optional>
#include <iterator>
#include <tuple>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <entt/entity/registry.hpp>
#include "Gng2D/core/scene_registry.hpp"
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/types/coroutine.hpp"

namespace Gng2D
{
struct Application;
struct Scene
{
    Scene()             = default;
    Scene(const Scene&) = delete;
    Scene(Scene&&)      = delete;
    virtual ~Scene()    = default;

    auto operator=(Scene&)  = delete;
    auto operator=(Scene&&) = delete;

    virtual void onEnter()              = 0;
    virtual void onExit()               = 0;
    virtual bool isCompleted()          = 0;
    virtual void update()               = 0;
    virtual void render(SDL_Renderer*)  = 0;

    virtual void onKeyDown(SDL_KeyboardEvent&)  {};
    virtual void onKeyUp(SDL_KeyboardEvent&)    {};

    void operator()();
    bool isPaused()     const;

    template<typename Coro, typename... Args>
    void addCoroutine(Coro coro, Args&&... args)
    {
        coroutines.emplace_back(coro, std::forward<Args>(args)...);
    }

///// Entity management /////
    template<typename Obj, typename... Args>
        requires(std::is_base_of<GameObject, Obj>::value)
    Obj spawn(Args&&... args)
    {
        using ObjTag = GameObject::TypeTag<Obj>;

        Obj o(*this);
        o.template addComponent<ObjTag>();
        o.onCreate(std::forward<Args>(args)...);

        constexpr bool hasDestroyFunction = requires(Obj& o)
        {
            o.onDestroy();
        };
        if constexpr (hasDestroyFunction)
        {
            o.template addComponent<CallDestroy>([](Scene& s, entt::entity e)
            {
                Obj(s, e).onDestroy();
            });
        }
        return o;
    }

    template<typename... Components>
    auto view()
    {
        return View<Components...>(*this, registry);
    }

    template<typename... OwnedComponents>
    auto group()
    {
        return Group<OwnedComponents...>(*this, registry);
    }

    template<typename Component>
    auto onConstruct()
    {
        return registry.on_construct<Component>();
    }

    template<typename Component>
    auto onUpdate()
    {
        return registry.on_update<Component>();
    }

    std::optional<GameObject>
        getGameObject(const std::string&);
    GameObject  getGameObject(entt::entity id);
    bool        entityExists(entt::entity id) const;
    void        destroyEntity(entt::entity id);

///// Other /////
    bool        isKeyPressed(SDL_Scancode) const;

protected:
    bool                pause{false};
    SceneRegistry       sceneRegistry;

private:
    void        runCoroutines();

    struct CallDestroy : std::function<void(Scene&, entt::entity)> {};

    entt::registry                  registry;
    std::vector<Coroutine>          coroutines;

    std::unordered_map<std::string, entt::entity>
        namedEntities;
    void removeNamedEntity(entt::registry&, entt::entity);

    friend struct ::Gng2D::GameObject;

///// View and Group /////
public:

    template<typename... Components>
    struct View 
    {
        using EnttView = decltype(registry.view<Components...>());
        using ViewIterator = decltype(registry.view<Components...>().each().begin());

        View(Scene& s, entt::registry& r)
            : scene(s)
            , enttView(r.view<Components...>()) {}

        struct Iterator 
        {
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;

            Iterator(ViewIterator&& ei, Scene& s)
                : enttIterator(ei)
                , scene(s) {}

            auto operator*()
            {
                return std::apply([&](auto id, auto&&... rest)
                {
                    return std::tuple_cat(std::make_tuple(scene.getGameObject(id)), std::tie(rest...));
                }, *enttIterator);
            }

            Iterator& operator++() 
            {
                enttIterator++;
                return *this;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) 
            { 
                return lhs.enttIterator == rhs.enttIterator;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs.enttIterator != rhs.enttIterator;
            }

        private:
            ViewIterator    enttIterator;
            Scene&          scene;
        };

        Iterator begin() { return Iterator(enttView.each().begin(), scene); };
        Iterator end()   { return Iterator(enttView.each().end(), scene);   };

    private:
        Scene&      scene;
        EnttView    enttView;
    };

    template<typename... Components>
    struct Group
    {
        using EnttGroup = decltype(registry.group<Components...>());
        using GroupIterator = decltype(registry.group<Components...>().each().begin());

        Group(Scene& s, entt::registry& r)
            : scene(s)
            , enttGroup(r.group<Components...>()) {}

        struct Iterator 
        {
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;

            Iterator(GroupIterator&& ei, Scene& s)
                : enttIterator(ei)
                , scene(s) {}

            auto operator*()
            {
                return std::apply([&](auto id, auto&&... rest)
                {
                    return std::tuple_cat(std::make_tuple(scene.getGameObject(id)), std::tie(rest...));
                }, *enttIterator);
            }

            Iterator& operator++() 
            {
                enttIterator++;
                return *this;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) 
            { 
                return lhs.enttIterator == rhs.enttIterator;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs.enttIterator != rhs.enttIterator;
            }

        private:
            GroupIterator    enttIterator;
            Scene&          scene;
        };

        Iterator begin() { return Iterator(enttGroup.each().begin(), scene); };
        Iterator end()   { return Iterator(enttGroup.each().end(), scene);   };
        
        void sort(std::function<bool(GameObject, GameObject)> f)
        {
            auto compfunc = [&](entt::entity r, entt::entity l)
            {
                return f(GameObject(scene, r), GameObject(scene, l));
            };
            return enttGroup.sort(compfunc);
        }
    private:
        Scene&      scene;
        EnttGroup   enttGroup;
    };
};
}

