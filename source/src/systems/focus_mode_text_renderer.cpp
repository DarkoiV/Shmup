#include "systems/focus_mode_text_renderer.hpp"

using Gng2D::Coroutine;
using Gng2D::gui::Text;

static Coroutine pulse(Text& t)
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

FocusModeTextRenderer::FocusModeTextRenderer(Gng2D::Scene& s)
    : scene(s)
{
    textAnimation = Coroutine(pulse, focus);
    focus.setOriginPoint(5, 5);
}

void FocusModeTextRenderer::operator()(SDL_Renderer* r)
{
    textAnimation();
    focus.render(r);
}
