#pragma once
#include "Gng2D/types/scene.hpp"
#include "Gng2D/gui/text.hpp"

struct FocusModeTextRenderer
{
    FocusModeTextRenderer(Gng2D::Scene& s);

    void operator()();
private:
    Gng2D::Scene&       scene;
    Gng2D::gui::Text    focus{"charmap-oldschool_white", "FOCUS"};
    Gng2D::Coroutine    textAnimation;
};

