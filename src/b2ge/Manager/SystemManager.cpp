//
// Created by brd6 on 31/08/2017.
//

#include "b2ge/Manager/SystemManager.hpp"
#include "b2ge/Core/World.hpp"

namespace b2ge
{
  bool SystemManager::has(SystemId id)
  {
    return mSystems.count(id) > 0;
  }

  void SystemManager::registerSystemFilterGroupId(System *system)
  {
    auto groupId = system->getComponentFilterGroupId();

    mWorld->getEntityManager().registerSystemComponentFilterGroupId(groupId);
  }

  void SystemManager::update(float deltaTime)
  {
    for (auto &it : mSystemUpdatables)
    {
      it.second->update(deltaTime);
    }
  }

  void SystemManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    for (auto &it : mSystemDrawables)
      {
	it.second->draw(target, states);
      }
  }

  void SystemManager::processEvents(sf::Event event)
  {
    for (auto &it : mSystemEventables)
      {
	it.second->processEvents(event);
      }
  }

  void SystemManager::addEntity(std::shared_ptr<Entity> entity,
				ComponentFilterGroupId groupId)
  {
    for (auto &it : mSystems)
      {
	if (it.second->getComponentFilterGroupId() == groupId)
	  {
	    it.second->addEntity(entity);
	  }
      }
  }

  void SystemManager::removeEntity(std::shared_ptr<Entity> entity,
				   ComponentFilterGroupId groupId)
  {
    for (auto &it : mSystems)
      {
	if (it.second->getComponentFilterGroupId() == groupId)
	  {
	    it.second->removeEntity(entity);
	  }
      }
  }
}