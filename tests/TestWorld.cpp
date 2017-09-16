//
// Created by brd6 on 29/08/17.
//

#include <b2ge/Manager/EntityManager.hpp>
#include <b2ge/Core/World.hpp>
#include <gtest/gtest.h>
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

TEST(TestWorld, SystemWithEntitiesMultiComponentRequiredForSystem)
{
  b2ge::World world;
  float deltaTime = 0.5f;

  auto &entity1 = world.getEntityManager().create("entity1");
  auto &entity2 = world.getEntityManager().create("entity2");
  auto &entity3 = world.getEntityManager().create("entity3");

  // MATCH : CollisionSystem, SpriteRender
  entity1.addComponent<Sprite>().texturePath = "test/texture/path";
  entity1.addComponent<Player>();

  // MATCH :
  entity2.addComponent<Player>().name = "PlayerName";

  // MATCH : SpriteRender
  entity3.addComponent<Sprite>().texturePath = "test/texture/path2";

  world.getSystemManager().add<SpriteRenderSystem>();
  world.getSystemManager().add<CollisionSystem>();

  auto &spriteRenderSystem = world.getSystemManager().get<SpriteRenderSystem>();
  auto &collisionSystem = world.getSystemManager().get<CollisionSystem>();

  // Update the world
  world.update(deltaTime);

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 3);
  EXPECT_EQ(collisionSystem.getEntitiesSize(), 1);
  EXPECT_EQ(spriteRenderSystem.getEntitiesSize(), 2);
}

TEST(TestWorld, SystemWithEntitiesNotWorldUpdate)
{
  b2ge::World world;
  float deltaTime = 0.5f;

  auto &entity1 = world.getEntityManager().create("entity1");
  auto &entity2 = world.getEntityManager().create("entity2");
  auto &entity3 = world.getEntityManager().create("entity3");

  // MATCH : CollisionSystem, SpriteRender
  entity1.addComponent<Sprite>().texturePath = "test/texture/path";
  entity1.addComponent<Player>();

  // MATCH :
  entity2.addComponent<Player>().name = "PlayerName";

  // MATCH : SpriteRender
  entity3.addComponent<Sprite>().texturePath = "test/texture/path2";

  world.getSystemManager().add<SpriteRenderSystem>();
  world.getSystemManager().add<CollisionSystem>();

  auto &spriteRenderSystem = world.getSystemManager().get<SpriteRenderSystem>();
  auto &collisionSystem = world.getSystemManager().get<CollisionSystem>();

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 3);
  EXPECT_EQ(collisionSystem.getEntitiesSize(), 0);
  EXPECT_EQ(spriteRenderSystem.getEntitiesSize(), 0);
}

TEST(TestWorld, KilledEntityInWorld)
{
  b2ge::World world;
  float deltaTime = 0.5f;

  auto &entity1 = world.getEntityManager().create("entity1");
  auto &entity2 = world.getEntityManager().create("entity2");

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 2);

  entity1.destroy();

  EXPECT_EQ(entity1.isDestroyed(), true);

  world.update(deltaTime);

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 1);
}

TEST(TestWorld, DisabledEntityInWorld)
{
  b2ge::World world;
  float deltaTime = 0.5f;

  auto &entity1 = world.getEntityManager().create("entity1");
  auto &entity2 = world.getEntityManager().create("entity2");

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 2);

  entity1.setActive(false);

  EXPECT_EQ(entity1.isActive(), false);

  world.update(deltaTime);

  EXPECT_EQ(world.getEntityManager().getActivated().size(), 1);
}