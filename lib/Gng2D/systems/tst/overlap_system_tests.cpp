#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/circle_colider.hpp"
#include "Gng2D/systems/overlap_system.hpp"

namespace
{
struct ColliderA : public Gng2D::CircleCollider {};
struct ColliderB : public Gng2D::CircleCollider {};

struct MockScene : Gng2D::Scene
{
    MOCK_METHOD(void, onEnter, (), (override));
    MOCK_METHOD(void, onExit, (), (override));
    MOCK_METHOD(bool, isCompleted, (), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, render, (), (override));
};

struct EntityA : Gng2D::GameObject
{
    EntityA(Gng2D::Scene& s, Gng2D::Position p, Gng2D::CircleCollider cc)
        : Gng2D::GameObject(s)
    {
        addComponent<Gng2D::Position>(p); 
        addComponent<ColliderA>(cc);
    };
};

struct EntityB : Gng2D::GameObject
{
    EntityB(Gng2D::Scene& s, Gng2D::Position p, Gng2D::CircleCollider cc)
        : Gng2D::GameObject(s)
    {
        addComponent<Gng2D::Position>(p); 
        addComponent<ColliderB>(cc);
    };
};

struct MockOverlapSystem : Gng2D::OverlapSystem<ColliderA, ColliderB>
{
    MockOverlapSystem(Gng2D::Scene& s)
        : Gng2D::OverlapSystem<ColliderA, ColliderB>(s) {}
    MOCK_METHOD(void, onOverlap, (entt::entity, entt::entity), (override));
};

constexpr auto RADIUS_1_UNIT = 1;
constexpr auto RADIUS_3_UNIT = 3;
}

using ::testing::_;

struct OverlapSystemTests : public ::testing::Test 
{
    MockScene               scene;
    MockOverlapSystem       overlapSystem{scene};

};

TEST_F(OverlapSystemTests, NoColliders)
{
    EXPECT_CALL(overlapSystem, onOverlap(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_NoCollision)
{
    EntityA entityA1(scene, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(scene, Gng2D::Position{1,6},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(scene, Gng2D::Position{10,9}, Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(scene, Gng2D::Position{16,9}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    EXPECT_CALL(overlapSystem, onOverlap(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_OverlapingCollidersOfSameType_NoCollision)
{
    EntityA entityA1(scene, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(scene, Gng2D::Position{5,10}, Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(scene, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(scene, Gng2D::Position{5,10}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    EXPECT_CALL(overlapSystem, onOverlap(_,_)).Times(0);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_OneCollision)
{
    EntityA entityA1(scene, Gng2D::Position{0,4},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(scene, Gng2D::Position{1,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(scene, Gng2D::Position{15,4}, Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(scene, Gng2D::Position{1,60}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    const auto A1Id = entityA1.getId();
    const auto B1Id = entityB1.getId();
    EXPECT_CALL(overlapSystem, onOverlap(A1Id, B1Id)).Times(1);
    overlapSystem();
}

TEST_F(OverlapSystemTests, FourColliders_ThreeCollisions)
{
    EntityA entityA1(scene, Gng2D::Position{0,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityB entityB1(scene, Gng2D::Position{1,5},  Gng2D::CircleCollider{RADIUS_1_UNIT});
    EntityA entityA2(scene, Gng2D::Position{3,5},  Gng2D::CircleCollider{RADIUS_3_UNIT});
    EntityB entityB2(scene, Gng2D::Position{4,10}, Gng2D::CircleCollider{RADIUS_3_UNIT});

    const auto A1Id = entityA1.getId();
    const auto B1Id = entityB1.getId();
    const auto A2Id = entityA2.getId();
    const auto B2Id = entityB2.getId();
    EXPECT_CALL(overlapSystem, onOverlap(A1Id, B1Id)).Times(1);
    EXPECT_CALL(overlapSystem, onOverlap(A2Id, B1Id)).Times(1);
    EXPECT_CALL(overlapSystem, onOverlap(A2Id, B2Id)).Times(1);
    overlapSystem();
}
