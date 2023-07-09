#include <gtest/gtest.h>
#include <domino/domino.h>

TEST(DominoTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
