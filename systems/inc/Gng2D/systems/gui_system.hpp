#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/position.hpp"

namespace Gng2D
{
struct GuiSystem 
{
    GuiSystem(entt::registry&);
    GuiSystem(const GuiSystem&) = delete;
    GuiSystem(GuiSystem&&)      = delete;
    ~GuiSystem();

    void operator()();

    entt::entity createText(const std::string& font, 
                            const std::string& str,
                            Gng2D::Position,
                            float scale = 1,
                            uint8_t layer = 100);

private:
    entt::registry& reg;

    static void attachTextSprite(entt::registry&, entt::entity);
    static void updateTextSprite(entt::registry&, entt::entity);
};
}

