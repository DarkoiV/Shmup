#include "Gng2D/systems/gui_factory.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/sprite.hpp"

using Gng2D::GuiFactory;

GuiFactory::GuiFactory(entt::registry& r)
    : reg(r)
{
}

Gng2D::EntityBuilder GuiFactory::createText(const std::string& font,
                                            const std::string& str,
                                            Gng2D::Position pos,
                                            float scale,
                                            uint8_t layer)
{
    return EntityBuilder(reg)
        .with<Layer>(layer)
        .with<Position>(pos)
        .with<Text>(font, str)
        .modify<Sprite>([scale](auto& sprite)
        {
            sprite.scale = scale;
        });
}

