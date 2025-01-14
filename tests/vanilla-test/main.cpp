#include <gtest/gtest.h>

TEST(Vanilla, Boolean) {
  ASSERT_TRUE(true);
  ASSERT_FALSE(false);
  ASSERT_EQ(true, true);
  ASSERT_EQ(false, false);
  ASSERT_NE(false, true);
  ASSERT_NE(true, false);
}