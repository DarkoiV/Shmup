#include "Gng2D/systems/gui_system.hpp"
#include "Gng2D/components/sprite.hpp"
#include "Gng2D/components/text.hpp"

using Gng2D::GuiSystem;


GuiSystem::GuiSystem(Scene& s)
    : scene(s)
{
    scene.onConstruct<Text>().connect<&attachTextSprite>();
    scene.onUpdate<Text>().connect<&updateTextSprite>();
}

GuiSystem::~GuiSystem()
{
    scene.onConstruct<Text>().disconnect<&attachTextSprite>();
    scene.onUpdate<Text>().disconnect<&updateTextSprite>();
}

void GuiSystem::attachTextSprite(entt::registry& r, entt::entity e)
{
    r.emplace_or_replace<Gng2D::Sprite>(e, r.get<Gng2D::Text>(e));
}

void GuiSystem::updateTextSprite(entt::registry& r, entt::entity e)
{
    r.replace<Gng2D::Sprite>(e, r.get<Gng2D::Text>(e));
}

