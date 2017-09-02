//
// Created by brd6 on 30/08/2017.
//

#include <iostream>
#include "Core/World.hpp"

namespace b2ge
{
  EntityManager &World::getEntityManager()
  {
    return mEntityManager;
  }

  SystemManager &World::getSystemManager()
  {
    return mSystemManager;
  }

  void World::update(float deltaTime)
  {
    mEntityManager.update();
  }

  World::World()
  {
    mEntityManager.mWorld = this;
    mSystemManager.mWorld = this;
  }
}