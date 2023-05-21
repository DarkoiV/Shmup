#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/text.hpp"

using Gng2D::GuiSystem;

GuiSystem::GuiSystem(entt::registry& r)
    : reg(r)
{
    reg.on_construct<Text>()
        .connect<&attachTextSprite>();
    reg.on_update<Text>()
        .connect<&updateTextSprite>();
}

GuiSystem::~GuiSystem()
{
    reg.on_construct<Text>()
        .disconnect<&attachTextSprite>();
    reg.on_update<Text>()
        .disconnect<&updateTextSprite>();
}

void GuiSystem::attachTextSprite(entt::registry& r, entt::entity e)
{
    r.emplace_or_replace<Gng2D::Sprite>(e, r.get<Gng2D::Text>(e));
}

void GuiSystem::updateTextSprite(entt::registry& r, entt::entity e)
{
    r.replace<Gng2D::Sprite>(e, r.get<Gng2D::Text>(e));
}

