#include "Gng2D/types/coroutine.hpp"
#include "Gng2D/core/log.hpp"

using namespace Gng2D;

Coroutine::HandleType Coroutine::promise_type::get_return_object()
{
    return {std::coroutine_handle<promise_type>::from_promise(*this)};
}

void Coroutine::promise_type::unhandled_exception()
{
    LOG::ERROR("Unhandled exception in coroutine");
}

std::suspend_always Coroutine::promise_type::yield_value(Status s)
{
    retVal = s;
    return {};
}

void Coroutine::promise_type::return_void()
{
    retVal = Completed{};
}

Coroutine::Coroutine()
{
    handle = nullptr;
    status = Completed{};
}

Coroutine::~Coroutine()
{
    if (handle) handle.destroy();
}

Coroutine::Coroutine(Coroutine&& from)
{
    handle = from.handle;
    from.handle = nullptr;
    from.status = Completed{};
}

Coroutine& Coroutine::operator=(Coroutine&& from)
{
    if (handle) handle.destroy();
    handle = from.handle;
    status = from.status;
    from.handle = nullptr;
    from.status = Completed{};

    return *this;
}

void Coroutine::operator()()
{
    if (not resumable()) return;
    handle.resume();
    status = handle.promise().retVal;
}

template<class... Ts> struct Overload : Ts... { using Ts::operator()...; };
template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

bool Coroutine::resumable()
{
    return std::visit(Overload{
        [](Completed&) -> bool 
        { 
            return false; 
        },
        [](WaitTicks& wt) -> bool
        {
            if (wt == 0) return true;
            --wt;
            return false;
        }
    }, status);
}

