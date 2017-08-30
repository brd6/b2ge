//
// Created by brd6 on 29/08/17.
//

#include <Manager/EntityManager.hpp>
#include "gtest/gtest.h"
#include "Core/Entity.hpp"
#include "Components.hpp"

TEST(TestEntities, CreateEntity)
{
  auto entity = new b2ge::Entity();

  EXPECT_EQ(entity->isActive() && !entity->isDestroyed(), true);
}

TEST(TestEntities, CreateEntityWithEntityManager)
{
  b2ge::EntityManager em;

  auto &entity = em.createEntity();

  EXPECT_EQ(entity.isActive() && !entity.isDestroyed(), true);
}

TEST(TestEntities, GetEntityByIdFromEntityManager)
{
  b2ge::EntityManager em;

  auto &entity = em.createEntity();

  // retrieve the entity ID
  auto entityId = entity.getId();

  auto &entity2 = em.get(entityId);

  EXPECT_EQ(entity, entity2);
}

TEST(TestEntities, GetEntityByNameFromEntityManager)
{
  b2ge::EntityManager em;

  std::string entityName{"myEntity"};

  // entity reference is not keeped immediately
  em.createEntity(entityName);

  auto &entity = em.get(entityName);

  EXPECT_EQ(entity.getName(), entityName);
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

TEST(TestEntities, RemoveComponent)
{
  auto entity = new b2ge::Entity();

  entity->addComponent<Vector2D>();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), true);

  entity->removeComponent<Vector2D>();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), false);
}

TEST(TestEntities, RemoveAllComponents)
{
  auto entity = new b2ge::Entity();

  entity->addComponent<Vector2D>();
  entity->addComponent<Sprite>();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), true);
  EXPECT_EQ(entity->hasComponent<Sprite>(), true);

  entity->removeComponent<Vector2D>();
  entity->removeComponent<Sprite>();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), false);
  EXPECT_EQ(entity->hasComponent<Sprite>(), false);
}

TEST(TestEntities, RemoveAllComponents2)
{
  auto entity = new b2ge::Entity();

  entity->addComponent<Vector2D>();
  entity->addComponent<Sprite>();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), true);
  EXPECT_EQ(entity->hasComponent<Sprite>(), true);

  entity->removeAllComponents();

  EXPECT_EQ(entity->hasComponent<Vector2D>(), false);
  EXPECT_EQ(entity->hasComponent<Sprite>(), false);
}

TEST(TestEntities, AddEntityToEntityManager)
{
  b2ge::EntityManager em;

  auto entity = new b2ge::Entity();

  EXPECT_NO_THROW(em.add(entity));
}

TEST(TestEntities, AddEntityToEntityManager2)
{
  b2ge::EntityManager em;

  EXPECT_NO_THROW(em.createEntity());
}

TEST(TestEntities, AddEntityWithComponentsToEntityManager)
{
  b2ge::EntityManager em;

  auto &entity = em.createEntity();

  EXPECT_NO_THROW(entity.addComponent<Vector2D>());
  EXPECT_NO_THROW(entity.addComponent<Sprite>());
}

TEST(TestEntities, MultipleAddEntityToEntityManager)
{
  b2ge::EntityManager em;

  EXPECT_NO_THROW(em.createEntity());
  EXPECT_NO_THROW(em.createEntity());
  EXPECT_NO_THROW(em.createEntity());
  EXPECT_NO_THROW(em.createEntity());
  EXPECT_NO_THROW(em.createEntity());
  EXPECT_NO_THROW(em.createEntity());
}

TEST(TestEntities, MultipleAddEntityToEntityManager2)
{
  b2ge::EntityManager em;

  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
  EXPECT_NO_THROW(em.add(new b2ge::Entity()));
}

TEST(TestEntities, MultipleAddAndGetEntityToEntityManager)
{
  b2ge::EntityManager em;

  em.add(new b2ge::Entity("myEntity1"));
  em.add(new b2ge::Entity("myEntity2"));
  em.add(new b2ge::Entity("myEntity3"));

  EXPECT_EQ(em.get("myEntity1").getName(), "myEntity1");
  EXPECT_EQ(em.get("myEntity2").getName(), "myEntity2");
  EXPECT_EQ(em.get("myEntity3").getName(), "myEntity3");
}