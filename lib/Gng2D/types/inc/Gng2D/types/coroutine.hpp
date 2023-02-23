#pragma once
#include <coroutine>
#include <functional>
#include <variant>

namespace Gng2D
{
struct Coroutine
{
    struct promise_type;

    using  WaitTicks    = unsigned;
    struct Completed {};
    using  Status       = std::variant<WaitTicks, Completed>;

    using HandleType    = std::coroutine_handle<promise_type>;
    struct promise_type
    {
        promise_type()  noexcept    = default;
        ~promise_type() noexcept    = default;

        HandleType              get_return_object();
        std::suspend_always     initial_suspend()       { return {}; };
        std::suspend_always     final_suspend()         { return {}; };
        void                    unhandled_exception();
        std::suspend_always     yield_value(Status);
        void                    return_void();
        Status retVal;
    };

    template<typename Coro, typename... Args>
    Coroutine(Coro coro, Args... args)
    {
        handle = coro(args...);
    }

    Coroutine();
    ~Coroutine();
    Coroutine(Coroutine&)               = delete;
    Coroutine(Coroutine&&);
    Coroutine& operator=(Coroutine&)    = delete;
    Coroutine& operator=(Coroutine&&);

    void operator()();

private:
    HandleType  handle;
    Status      status;

    bool resumable();
};
}

