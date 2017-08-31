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

TEST(TestWorld, ValideEntityManagerAccess)
{
  b2ge::World world;
  auto *em = new b2ge::EntityManager();

  world.setEntityManager(em);

  EXPECT_NO_THROW(world.getEntityManager());
}

TEST(TestWorld, ValidSystemManagerAccess)
{
  b2ge::World world;
  auto *sm = new b2ge::SystemManager();

  world.setSystemManager(sm);

  EXPECT_NO_THROW(world.getSystemManager());
}