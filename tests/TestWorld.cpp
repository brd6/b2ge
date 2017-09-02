//
// Created by brd6 on 29/08/17.
//

#include "Manager/EntityManager.hpp"
#include "Core/World.hpp"
#include "gtest/gtest.h"
#include "Components.hpp"
#include "Systems.hpp"

TEST(TestWorld, ValideEntityManagerAccess)
{
  b2ge::World world;

  EXPECT_NO_THROW(world.getEntityManager());
}

TEST(TestWorld, ValidSystemManagerAccess)
{
  b2ge::World world;

  EXPECT_NO_THROW(world.getSystemManager());
}

TEST(TestWorld, SystemWithEntities)
{
  b2ge::World world;
  float deltaTime = 0.5f;

  auto &entity1 = world.getEntityManager().create();
  auto &entity2 = world.getEntityManager().create();
  auto &entity3 = world.getEntityManager().create();

  entity1.addComponent<Sprite>().texturePath = "test/texture/path";
  entity2.addComponent<Player>().name = "PlayerName";
  entity3.addComponent<Sprite>().texturePath = "test/texture/path2";

  world.getSystemManager().add<SpriteRenderSystem>();

  // Update the world
  world.update(deltaTime);

  auto &spriteRenderSystem = world.getSystemManager().get<SpriteRenderSystem>();

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 3);
  EXPECT_EQ(spriteRenderSystem.getEntitiesSize(), 2);
}