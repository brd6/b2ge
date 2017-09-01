//
// Created by brd6 on 30/08/17.
//

#include <algorithm>
#include "Manager/EntityManager.hpp"

namespace b2ge
{
  void EntityManager::add(Entity *entity)
  {
    entity->mWorld = mWorld;
    std::unique_ptr<Entity> entityPtr{entity};

    mEntities[entity->getId()] = std::move(entityPtr);
  }

  Entity &EntityManager::get(std::string const &name)
  {
    auto it = std::find_if(std::begin(mEntities), std::end(mEntities),
			   [name](auto &entity) {
			     return (entity.second->getName() == name);
			   });
    if (it == std::end(mEntities))
      throw std::logic_error("Entity '" + name + "' not found.");
    return *((it->second).get());
  }

  Entity &EntityManager::create()
  {
    return create("");
  }

  Entity &EntityManager::create(std::string const &name = "")
  {
    auto *entity = new Entity(name);

    add(entity);

    return *entity;
  }

  void EntityManager::removeEntitiesDestroyed()
  {
    mEntities.erase(
	    std::find_if(std::begin(mEntities), std::end(mEntities),
			 [](auto &entity) {
			   return (entity.second->isDestroyed());
			 }),
	    std::end(mEntities)
    );
  }

  Entity &EntityManager::get(std::size_t id)
  {
    return *(mEntities[id].get());
  }

  const Entities &EntityManager::getActivated() const
  {
    return mEntitiesActivated;
  }

  const Entities &EntityManager::getDeactivated() const
  {
    return mEntitiesDeactivated;
  }

  const Entities &EntityManager::getDestroyed() const
  {
    return mEntitiesDestroyed;
  }

  const Entities &EntityManager::getByComponentFilterGroupId(ComponentFilterGroupId id) const
  {
    return mEntitiesFiltered.at(id);
  }

  void EntityManager::update()
  {
    mEntitiesActivated.clear();
    mEntitiesDestroyed.clear();
    mEntitiesDeactivated.clear();

    for (auto &it : mEntities)
      {
	auto entity = it.second.get();

	if (entity->isDestroyed())
	  {

	  }
      }

    for (auto &it : mEntitiesFiltered)
      {
	std::remove_if(std::begin(it.second), std::end(it.second), [](auto &entity) {
	  return (entity.isDestroyed() || !entity.isActive());
	});

	for (auto &entityActivated : mEntitiesActivated)
	  {
	    if (it.first & entityActivated.getId())
	      it.second.push_back(entityActivated);
	  }
      }
  }

}
