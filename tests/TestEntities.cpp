//
// Created by brd6 on 29/08/17.
//

#include "gtest/gtest.h"
#include "Core/Entity.hpp"
#include "Components.hpp"

TEST(TestEntities, CreateEntity)
{
  auto entity = new b2ge::Entity();

  EXPECT_EQ(entity->isActive() && !entity->isDestroyed(), true);
}

TEST(TestEntities, AddComponent)
{
  auto entity = new b2ge::Entity();

  EXPECT_NO_THROW(entity->addComponent<Vector2D>());
}

TEST(TestEntities, AddMultipleComponents)
{
  auto entity = new b2ge::Entity();

  EXPECT_NO_THROW(entity->addComponent<Vector2D>());
  EXPECT_NO_THROW(entity->addComponent<Sprite>());
  EXPECT_NO_THROW(entity->addComponent<Player>());
}

TEST(TestEntities, TryToAddMultipleSameComponents)
{
  auto entity = new b2ge::Entity();

  EXPECT_NO_THROW(entity->addComponent<Vector2D>());
  EXPECT_THROW(entity->addComponent<Vector2D>(), std::logic_error);
  EXPECT_THROW(entity->addComponent<Vector2D>(), std::logic_error);
}

TEST(TestEntities, GetComponent)
{
  auto entity = new b2ge::Entity();

  entity->addComponent<Vector2D>();

  EXPECT_NO_THROW(entity->getComponent<Vector2D>());
}

TEST(TestEntities, TryGetComponentThatDoesntExist)
{
  auto entity = new b2ge::Entity();

  EXPECT_THROW(entity->getComponent<Vector2D>(), std::logic_error);
}
