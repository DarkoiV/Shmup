#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/sprite.hpp"

using Gng2D::GuiSystem;

GuiSystem::GuiSystem(entt::registry& r)
    : reg(r)
{
    connectGuiComponent<Text>(reg);
}

GuiSystem::~GuiSystem()
{
    disconnectGuiComponent<Text>(reg);
}

