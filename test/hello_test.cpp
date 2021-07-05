//
// Created by nim on 05.07.2021.
//

#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "word");
  EXPECT_EQ(7 * 6, 42);
}
