#pragma once
#include "Gng2D/types/scene.hpp"

namespace Gng2D
{
struct GuiSystem 
{
    GuiSystem(Scene&);
    GuiSystem(const GuiSystem&) = delete;
    GuiSystem(GuiSystem&&)      = delete;
    ~GuiSystem();

    void operator()();

private:
    Scene& scene;

    static void attachTextSprite(entt::registry&, entt::entity);
    static void updateTextSprite(entt::registry&, entt::entity);
};
}

