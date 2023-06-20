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
    using ModFunc           = std::function<void(Text&)>;
    struct Element 
    {
        entt::entity    entity;
        SelectCallback  callback;
    };

    ModFunc                 onHighlight;
    ModFunc                 onStopHiglight;
    std::vector<Element>    elements;
    std::size_t             highlightedSelection;
};
}

