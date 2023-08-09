#include "Gng2D/scene/animaton_system.hpp"
#include <algorithm>
#include <execution>

using Gng2D::AnimationSystem;

AnimationSystem::AnimationSystem(entt::registry& r)
    : reg(r)
{
    reg.ctx().emplace<AnimationSystem&>(*this);
}

void AnimationSystem::operator()()
{
    auto view = reg.view<Animation>();
    view.each([&](auto entity, auto& animation)
    {
        animation();
        if (animation.isCompleted()) reg.erase<Animation>(entity);
    });
}

