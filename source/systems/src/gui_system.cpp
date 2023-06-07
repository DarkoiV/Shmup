#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/box.hpp"

using Gng2D::GuiSystem;

GuiSystem::GuiSystem(entt::registry& r)
    : reg(r)
{
    connectGuiComponent<Text>(reg);
    connectGuiComponent<Box>(reg);
}

GuiSystem::~GuiSystem()
{
    disconnectGuiComponent<Text>(reg);
    disconnectGuiComponent<Box>(reg);
}

