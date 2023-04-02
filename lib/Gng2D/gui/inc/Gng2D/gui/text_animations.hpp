#pragma once
#include "Gng2D/gui/text.hpp"
#include "Gng2D/types/coroutine.hpp"

namespace Gng2D::gui 
{
    Coroutine pulse(Text& t);
    Coroutine fadeIn(Text& t);
}

