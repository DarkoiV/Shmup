#include "Gng2D/gui/text_animations.hpp"

using Gng2D::Coroutine;

Coroutine Gng2D::gui::pulse(Text& t)
{
    while (true)
    {
        for (int i = 0; i <= 25; ++i)
        {
            t.setOpacity(255 - (i * 7));
            co_yield Coroutine::WaitTicks{2};
        }
        co_yield Coroutine::WaitTicks{15};
        for (int i = 25; i >= 0; --i)
        {
            t.setOpacity(255 - (i * 7));
            co_yield Coroutine::WaitTicks{2};
        }
        co_yield Coroutine::WaitTicks{15};
    }
}

Coroutine Gng2D::gui::fadeIn(Text& t)
{
    for (int i = 0; i <= 240; i += 2)
    {
        t.setOpacity(i);
        co_yield Coroutine::WaitTicks{1};
    }
    t.setOpacity(255);
}

