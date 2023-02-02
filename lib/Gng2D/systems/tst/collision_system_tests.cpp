#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/systems/collision_system.hpp"

namespace
{
struct ColliderA : Gng2D::CircleCollider {};
struct ColliderB : Gng2D::CircleCollider {};
}

using MockCollisionHandler = ::testing::MockFunction<void(entt::entity, entt::entity)>;
using ::testing::_;

TEST(CollisionSystemTests, NoColliders)
{
    entt::registry          registry;
    MockCollisionHandler    collisionHandler;

    Gng2D::CollisionSystem<ColliderA, ColliderB> 
        collisionSystem(registry, collisionHandler.AsStdFunction());

    EXPECT_CALL(collisionHandler, Call(_,_)).Times(0);
    collisionSystem();
}
