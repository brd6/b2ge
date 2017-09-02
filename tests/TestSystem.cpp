//
// Created by brd6 on 29/08/17.
//

#include "Core/World.hpp"
#include "gtest/gtest.h"
#include "Systems.hpp"

TEST(TestSystem, InvalidUseOfSystem)
{
  SpriteRenderSystem spriteRenderSystem;

  EXPECT_THROW(spriteRenderSystem.render(), std::runtime_error);
}

TEST(TestSystem, ValidUseOfSystem)
{
  b2ge::World world;

  // add system to the SystemManager
   world.getSystemManager().add<SpriteRenderSystem>();

  // get the system
   auto &spriteRenderSystem = world.getSystemManager().get<SpriteRenderSystem>();

  // use it
  EXPECT_EQ(spriteRenderSystem.itsWork(), true);
}

TEST(TestSystem, ValidUseOfSystemUpdatable)
{
  // In progress
}