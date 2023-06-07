#pragma once
#include <cstdint>
#include <vector>
#include <tuple>
#include <functional>
#include <entt/entt.hpp>

namespace Gng2D
{
struct Text;
struct SelectionList
{
    using SelectCallback    = std::function<void()>;
    using OnHighlight       = std::function<void(Text&)>;
    using OnStopHighlight   = std::function<void(Text&)>;
    using Element           = std::pair<entt::entity, SelectCallback>;

    OnHighlight             onHighlight;
    OnStopHighlight         onStopHiglight;
    std::vector<Element>    elements;
    std::size_t             highlightedSelection;
};
}

