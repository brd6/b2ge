//
// Created by brd6 on 29/08/17.
//

#include "Manager/EntityManager.hpp"
#include "Core/World.hpp"
#include "gtest/gtest.h"

TEST(TestWorld, InvalidEntityManagerAccess)
{
  b2ge::World world;

  EXPECT_THROW(world.getEntityManager(), std::runtime_error);
}

TEST(TestWorld, InvalidSystemManagerAccess)
{
  b2ge::World world;

  EXPECT_THROW(world.getSystemManager(), std::runtime_error);
}