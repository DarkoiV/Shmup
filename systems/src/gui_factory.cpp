#include "Gng2D/systems/gui_factory.hpp"
#include "Gng2D/components/box.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/text.hpp"

using Gng2D::GuiFactory;

GuiFactory::GuiFactory(entt::registry& r)
    : reg(r)
{
}

Gng2D::EntityCompositor GuiFactory::createText(const std::string& font,
                                            const std::string& str,
                                            Gng2D::Position pos,
                                            float scale,
                                            uint8_t layer)
{
    return EntityCompositor(reg)
        .with<Layer>(layer)
        .with<Position>(pos)
        .with<Text>(font, str)
        .modify<Sprite>([scale](auto& sprite)
        {
            sprite.scale = scale;
        });
}

Gng2D::EntityCompositor GuiFactory::createBox(const std::string& sprite,
                                           Gng2D::Position pos,
                                           unsigned capWidth,
                                           unsigned capHeight,
                                           unsigned capMargin,
                                           float scale,
                                           uint8_t layer)
{
    return EntityCompositor(reg)
        .with<Layer>(layer)
        .with<Position>(pos)
        .with<Box>(sprite, capWidth, capHeight, capMargin)
        .modify<Sprite>([scale](auto& sprite)
        {
            sprite.scale = scale;
        });
}

