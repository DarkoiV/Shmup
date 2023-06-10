#include "Gng2D/scene/gui_system.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/box.hpp"
#include "Gng2D/components/selection_list.hpp"
#include "Gng2D/core/log.hpp"

using Gng2D::GuiSystem;

GuiSystem::GuiSystem(entt::registry& r)
    : reg(r)
{
    connectGuiComponent<Text>(reg);
    connectGuiComponent<Box>(reg);

    reg.ctx().emplace<GuiSystem&>(*this);
}

GuiSystem::~GuiSystem()
{
    disconnectGuiComponent<Text>(reg);
    disconnectGuiComponent<Box>(reg);
}

void GuiSystem::activeMenuUp()
{
    if (activeMenu == entt::null) return LOG::WARN("No active menu");
    auto& slist     = reg.get<SelectionList>(activeMenu);
    auto& current   = slist.highlightedSelection;
    if (current == 0) return;

    auto oldSelection = slist.elements[current].first;
    auto newSelection = slist.elements[current-1].first;

    reg.patch<Text>(oldSelection, slist.onStopHiglight);
    reg.patch<Text>(newSelection, slist.onHighlight);
    current--;
}

void GuiSystem::activeMenuDown()
{
    if (activeMenu == entt::null) return LOG::WARN("No active menu");
    auto& slist     = reg.get<SelectionList>(activeMenu);
    auto& current   = slist.highlightedSelection;
    if (current + 1 >= slist.elements.size()) return;

    auto oldSelection = slist.elements[current].first;
    auto newSelection = slist.elements[current+1].first;

    reg.patch<Text>(oldSelection, slist.onStopHiglight);
    reg.patch<Text>(newSelection, slist.onHighlight);
    current++;
}

void GuiSystem::activeMenuSelect()
{
    if (activeMenu == entt::null) return LOG::WARN("No active menu");
    auto& slist = reg.get<SelectionList>(activeMenu);
    auto current = slist.highlightedSelection;

    auto callback = slist.elements[current].second;
    callback();
}

void GuiSystem::makeActiveMenu(entt::entity menu)
{
    if (not reg.try_get<SelectionList>(menu))
    {
        return LOG::ERROR("Menu entity is not a menu!");
    }
    activeMenu = menu;
}

