#include "Gng2D/scene/gui_system.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/box.hpp"
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

