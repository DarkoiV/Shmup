#pragma once
#include <coroutine>
#include <variant>
#include "Gng2D/core/log.hpp"
#include "Gng2D/types/scene.hpp"

namespace Gng2D
{
struct SceneControl 
{
    struct  Coroutine;
    struct  Promise;
    using   CoroHandle  = std::coroutine_handle<Promise>;
    using   WaitTicks   = unsigned;

    SceneControl(Scene& s, CoroHandle h);
    virtual ~SceneControl();

    void operator()();

private:
    Scene&      scene;
    CoroHandle  handle;
    bool        completed{false};
    WaitTicks   waitTicks{10};

/// Coroutine impl ///
public:
    struct Promise
    {
        Promise() noexcept  = default;
        ~Promise()          = default;

        Coroutine get_return_object()
        {
            return {std::coroutine_handle<Promise>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        void unhandled_exception() 
        {
            LOG::ERROR("Exception in coroutine!");
        };

        using Completed = std::monostate;
        using ReturnValue = std::variant<WaitTicks, Completed>;

        std::suspend_always yield_value(ReturnValue rv)
        {
            returnValue = rv;
            return {};
        }

        void return_void()
        {
            returnValue = Completed{};
        }

        ReturnValue returnValue;
    };
    struct Coroutine : std::coroutine_handle<Promise>
    {
        using promise_type = Promise;
    };
};
}

