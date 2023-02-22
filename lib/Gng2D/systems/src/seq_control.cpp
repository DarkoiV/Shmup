#include "Gng2D/systems/seq_control.hpp"

Gng2D::SeqControl::SeqControl(CoroHandle h)
    : handle(h)
{
}

Gng2D::SeqControl::~SeqControl()
{
    if (handle) handle.destroy();
}

void Gng2D::SeqControl::operator()()
{
    if (completed) return;
    if (waitTicks > 0)
    {
        waitTicks--;
        return;
    }

    handle.resume();
    auto status = handle.promise().status;
    if (std::holds_alternative<WaitTicks>(status)) 
    {
        waitTicks = std::get<WaitTicks>(status);
    }
    if (std::holds_alternative<Completed>(status)) 
    {
        completed = true;
        handle.destroy();
        handle = nullptr;
    }
}

