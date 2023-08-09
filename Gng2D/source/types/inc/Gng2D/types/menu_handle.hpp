#pragma once
#include <entt/entt.hpp>

namespace Gng2D
{
struct MenuHandle
{
    MenuHandle(entt::registry&, entt::entity);

    void up();
    void down();
    void select();

private:
    entt::registry&     reg;
    entt::entity        id;
};
}

