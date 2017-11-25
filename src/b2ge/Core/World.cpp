//
// Created by brd6 on 30/08/2017.
//

#include <b2ge/Core/World.hpp>

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
    mSystemManager.update(deltaTime);
  }

  World::World()
  {
    mEntityManager.mWorld = this;
    mSystemManager.mWorld = this;
  }

  void World::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    mSystemManager.draw(target, states);
  }

  void World::processEvents(sf::Event event)
  {
    mSystemManager.processEvents(event);
  }
}