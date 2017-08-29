//
// Created by brd6 on 29/08/17.
//

#include "gtest/gtest.h"

TEST(ExampleTest, Greet) {
  EXPECT_EQ(true, true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}