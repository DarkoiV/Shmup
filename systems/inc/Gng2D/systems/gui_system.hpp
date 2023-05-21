#pragma once
#include <entt/entt.hpp>

namespace Gng2D
{
struct GuiSystem 
{
    GuiSystem(entt::registry&);
    GuiSystem(const GuiSystem&) = delete;
    GuiSystem(GuiSystem&&)      = delete;
    ~GuiSystem();

    void operator()();

private:
    entt::registry& reg;

    static void attachTextSprite(entt::registry&, entt::entity);
    static void updateTextSprite(entt::registry&, entt::entity);
};
}

