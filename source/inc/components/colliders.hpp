#pragma once
#include "Gng2D/components/circle_colider.hpp"

struct PlayerCollider : Gng2D::CircleCollider {};
struct PlayerBulletCollider : Gng2D::CircleCollider {};
struct EnemyCollider : Gng2D::CircleCollider {};
struct EnemyBulletCollider : Gng2D::CircleCollider {};

