#pragma once
#include <entt/entt.hpp>
#include "Gng2D/components/animation.hpp"
#include "Gng2D/components/sprite.hpp"
#include "sprite_sheets.hpp"

using AnimationFunction = Gng2D::Coroutine(*)(entt::registry&, entt::entity);
void emplaceAnimation(AnimationFunction, entt::registry& reg, entt::entity);

Gng2D::Coroutine flashShip(entt::registry&, entt::entity ship);
Gng2D::Coroutine rotatePickup(entt::registry&, entt::entity pickup);
Gng2D::Coroutine laserShoot(entt::registry&, entt::entity);
Gng2D::Coroutine rotateChargeMarker(entt::registry&, entt::entity);

