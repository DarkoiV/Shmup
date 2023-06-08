#include "Gng2D/systems/animaton_system.hpp"
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
    std::for_each(std::execution::par_unseq, view.begin(), view.end(), 
    [&](auto entity)
    {
        auto&& [animation] = view.get(entity);
        animation();
        if (animation.isCompleted()) reg.erase<Animation>(entity);
    });
}

