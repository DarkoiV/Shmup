#pragma once
#include "Gng2D/types/entity_builder.hpp"
#include "Gng2D/components/position.hpp"

namespace Gng2D
{
struct GuiFactory 
{
    GuiFactory(entt::registry&);

    EntityBuilder createText(const std::string& font, 
                             const std::string& str,
                             Gng2D::Position,
                             float scale = 1.0f,
                             uint8_t layer = 100);

    EntityBuilder createBox(const std::string& sprite,
                            Gng2D::Position,
                            unsigned capacityWidth,
                            unsigned capacityheight,
                            unsigned capacityMargin = 0,
                            float scale = 1.0f,
                            uint8_t layer = 100);
private:
    entt::registry& reg;
};
}

