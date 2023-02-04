#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gng2D/components/game_object.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/systems/overlap_system.hpp"

namespace
{
struct ColliderA : public Gng2D::CircleCollider {};
struct ColliderB : public Gng2D::CircleCollider {};

struct EntityA : Gng2D::GameObject
{
    EntityA(entt::registry& r, Gng2D::Position p, Gng2D::CircleCollider cc)
        : Gng2D::GameObject(r)
    {
        addComponent<Gng2D::Position>(p); 
        addComponent<ColliderA>(cc);
    };
};

struct EntityB : Gng2D::GameObject
{
    EntityB(entt::registry& r, Gng2D::Position p, Gng2D::CircleCollider cc)
        : Gng2D::GameObject(r)
    {
        addComponent<Gng2D::Position>(p); 
        addComponent<ColliderB>(cc);
    };
};

constexpr auto RADIUS_1_UNIT = 1;
constexpr auto RADIUS_3_UNIT = 3;
}

using OnOverlapHandler = ::testing::MockFunction<void(entt::entity, entt::entity)>;
using ::testing::_;

struct OverlapSystemTests : public ::testing::Test 
{
    entt::registry          registry;
    OnOverlapHandler        onOverlapHandler;

    Gng2D::OverlapSystem<ColliderA, ColliderB> 
        overlapSystem{registry, onOverlapHandler.AsStdFunction()};

};

TEST_F(OverlapSystemTests, NoColliders)
{
    EXPECT_CALL(onOverlapHandler, Call(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_NoCollision)
{
    EntityA entityA1(registry, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(registry, Gng2D::Position{1,6},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(registry, Gng2D::Position{10,9}, Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(registry, Gng2D::Position{16,9}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    EXPECT_CALL(onOverlapHandler, Call(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_OverlapingCollidersOfSameType_NoCollision)
{
    EntityA entityA1(registry, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(registry, Gng2D::Position{5,10}, Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(registry, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(registry, Gng2D::Position{5,10}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    EXPECT_CALL(onOverlapHandler, Call(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_OneCollision)
{
    EntityA entityA1(registry, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(registry, Gng2D::Position{1,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(registry, Gng2D::Position{15,4}, Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(registry, Gng2D::Position{1,60}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    const auto A1Id = entityA1.getId();
    const auto B1Id = entityB1.getId();
    EXPECT_CALL(onOverlapHandler, Call(A1Id,B1Id)).Times(1);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_ThreeCollisions)
{
    EntityA entityA1(registry, Gng2D::Position{0,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(registry, Gng2D::Position{1,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(registry, Gng2D::Position{3,5},  Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(registry, Gng2D::Position{4,10}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    const auto A1Id = entityA1.getId();
    const auto B1Id = entityB1.getId();
    const auto A2Id = entityA2.getId();
    const auto B2Id = entityB2.getId();
    EXPECT_CALL(onOverlapHandler, Call(A1Id,B1Id)).Times(1);
    EXPECT_CALL(onOverlapHandler, Call(A2Id,B1Id)).Times(1);
    EXPECT_CALL(onOverlapHandler, Call(A2Id,B2Id)).Times(1);
    overlapSystem();
}
