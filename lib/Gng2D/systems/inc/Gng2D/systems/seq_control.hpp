#pragma once
#include <coroutine>
#include <variant>
#include "Gng2D/core/log.hpp"

namespace Gng2D
{
struct SeqControl 
{
    struct  Coroutine;
    struct  Promise;
    using   CoroHandle  = std::coroutine_handle<Promise>;
    using   WaitTicks   = unsigned;
    struct  Completed {};
    using   Status = std::variant<WaitTicks, Completed>;

    SeqControl(CoroHandle h);
    virtual ~SeqControl();

    void operator()();

private:
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
            return {CoroHandle::from_promise(*this)};
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

        std::suspend_always yield_value(Status s)
        {
            status = s;
            return {};
        }

        void return_void()
        {
            status = Completed{};
        }

        Status status;
    };

    struct Coroutine : std::coroutine_handle<Promise>
    {
        using promise_type = Promise;
    };
};

using Coroutine = SeqControl::Coroutine;
}

