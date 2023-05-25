#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/animation.hpp"
#include "Gng2D/components/sprite.hpp"
#include "sprite_sheets.hpp"

Gng2D::Coroutine flashShip(entt::registry& reg, entt::entity ship);

