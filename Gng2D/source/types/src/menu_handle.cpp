#include "Gng2D/types/menu_handle.hpp"
#include "Gng2D/components/selection_list.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/core/log.hpp"

using Gng2D::MenuHandle;

MenuHandle::MenuHandle(entt::registry& r, entt::entity id)
    : reg(r)
    , id(id)
{
}

void MenuHandle::up()
{
    if (id == entt::null) return LOG::WARN("No active menu");
    auto& slist     = reg.get<SelectionList>(id);
    auto& current   = slist.highlightedSelection;
    if (current == 0) return;

    auto oldSelection = slist.elements[current].entity;
    auto newSelection = slist.elements[current-1].entity;

    reg.patch<Text>(oldSelection, slist.onStopHiglight);
    reg.patch<Text>(newSelection, slist.onHighlight);
    current--;
}

void MenuHandle::down()
{
    if (id == entt::null) return LOG::WARN("No active menu");
    auto& slist     = reg.get<SelectionList>(id);
    auto& current   = slist.highlightedSelection;
    if (current + 1 >= slist.elements.size()) return;

    auto oldSelection = slist.elements[current].entity;
    auto newSelection = slist.elements[current+1].entity;

    reg.patch<Text>(oldSelection, slist.onStopHiglight);
    reg.patch<Text>(newSelection, slist.onHighlight);
    current++;
}

void MenuHandle::select()
{
    if (id == entt::null) return LOG::WARN("No active menu");
    auto& slist = reg.get<SelectionList>(id);
    auto current = slist.highlightedSelection;

    auto callback = slist.elements[current].callback;
    callback();
}

