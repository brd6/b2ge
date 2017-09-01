//
// Created by brd6 on 29/08/17.
//

#include "Core/World.hpp"
#include "gtest/gtest.h"
#include "Systems.hpp"

TEST(TestSystem, ValidGetSystemEntities)
{
  b2ge::World world;
  SpriteRenderSystem spriteRenderSystem;
  CollisionSystem collisionSystem;

  //spriteRenderSystem.getId()

//  EXPECT_THROW(world.getEntityManager(), std::runtime_error);
}