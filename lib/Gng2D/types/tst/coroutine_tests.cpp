#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gng2D/types/coroutine.hpp"

namespace
{
Gng2D::Coroutine empty()
{
    co_return;
}
Gng2D::Coroutine emptyBodyCoro{empty};

Gng2D::Coroutine waitXTicks(unsigned ticks, bool* beforeYield, bool* afterYield)
{
    *beforeYield = true;
    co_yield Gng2D::Coroutine::WaitTicks{ticks};
    *afterYield = true;
}
}

TEST(CoroutineTests, EmptyCoroutineObject_HasCompletedStatus)
{
    Gng2D::Coroutine emptyCoroutineObj;
    ASSERT_TRUE(emptyCoroutineObj.isCompleted());
}

TEST(CoroutineTests, EmptyCoroutineBody_IsNotCompletedUntillCalled)
{
    ASSERT_FALSE(emptyBodyCoro.isCompleted());
}

TEST(CoroutineTests, EmptyCoroutineBody_IsCompletedAfterBeingCalled)
{
    emptyBodyCoro();
    ASSERT_TRUE(emptyBodyCoro.isCompleted());
}

TEST(CoroutineTests, Coroutine_IsSafeToCallAfterCompletion)
{
    emptyBodyCoro();
    ASSERT_TRUE(emptyBodyCoro.isCompleted());
    emptyBodyCoro();
    emptyBodyCoro();
    ASSERT_TRUE(emptyBodyCoro.isCompleted());
}

TEST(CoroutineTests, Coroutine_CanBeMoved)
{
    auto newCoro = std::move(emptyBodyCoro);
    ASSERT_FALSE(newCoro.isCompleted());
    ASSERT_TRUE(emptyBodyCoro.isCompleted());
}

TEST(CoroutineTests, Coroutine_WillWaitXTicksBeforeResuming)
{
    constexpr unsigned X_TICKS = 20;
    bool checkpoint1{false}, checkpoint2{false};
    Gng2D::Coroutine waitXTicksCoro{waitXTicks, X_TICKS, &checkpoint1, &checkpoint2};

    waitXTicksCoro();
    ASSERT_TRUE(checkpoint1);

    for (unsigned i = 0; i < X_TICKS; i++) waitXTicksCoro();
    ASSERT_TRUE(checkpoint2);
}
