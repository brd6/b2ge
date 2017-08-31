//
// Created by brd6 on 30/08/2017.
//

#include <iostream>
#include "Core/World.hpp"

namespace b2ge
{
  EntityManager &World::getEntityManager() const
  {
    if (mEntityManager == nullptr)
      throw std::runtime_error("entityManager must be initialise before");

    return *(mEntityManager.get());
  }

  SystemManager &World::getSystemManager() const
  {
    if (mSystemManager == nullptr)
      throw std::runtime_error("systemManager must be initialise before");

    return *(mSystemManager.get());
  }

  void World::update(float deltaTime)
  {

  }

  void World::setEntityManager(EntityManager *entityManager)
  {
    if (entityManager != nullptr)
      entityManager->mWorld = this;
    mEntityManager.reset(entityManager);
  }

  void World::setSystemManager(SystemManager *systemManager)
  {
    if (systemManager != nullptr)
      systemManager->mWorld = this;
    mSystemManager.reset(systemManager);
  }
}