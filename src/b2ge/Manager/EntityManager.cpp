//
// Created by brd6 on 30/08/17.
//

#include <algorithm>
#include "Manager/EntityManager.hpp"

namespace b2ge
{
  Entity &EntityManager::get(EntityId id)
  {
    return *(mEntitiesActivated[id]);
  }

  Entity &EntityManager::get(std::string const &name)
  {
    auto it = std::find_if(std::begin(mEntitiesActivated), std::end(mEntitiesActivated),
			   [name](auto &entity) {
			     return (entity.second->getName() == name);
			   });
    if (it == std::end(mEntitiesActivated))
      throw std::logic_error("Entity '" + name + "' not found.");
    return *(it->second);
  }

  Entity &EntityManager::create()
  {
    return create("");
  }

  Entity &EntityManager::create(std::string const &name = "")
  {
    auto entity = std::make_shared<Entity>(name);

    mEntitiesActivated.emplace(entity->getId(), entity);

    entity->mWorld = mWorld;

    onEntityStateChanged(*entity);

    return *entity;
  }

  void EntityManager::removeEntitiesDestroyed()
  {
//    mEntities.erase(
//	    std::find_if(std::begin(mEntities), std::end(mEntities),
//			 [](auto &entity) {
//			   return (entity.second->isDestroyed());
//			 }),
//	    std::end(mEntities)
//    );
  }

  const EntitiesMap &EntityManager::getActivated() const
  {
    return mEntitiesActivated;
  }

  const EntitiesMap &EntityManager::getDeactivated() const
  {
    return mEntitiesDeactivated;
  }

  const EntitiesMap &EntityManager::getDestroyed() const
  {
    return mEntitiesDestroyed;
  }

  const EntitiesMap &EntityManager::getByComponentFilterGroupId(ComponentFilterGroupId id) const
  {
    return mEntitiesFiltered.at(id);
  }

  void EntityManager::update()
  {
    for(auto &entityId : mEntitiesIdStateChanged)
      {
	// mEntitiesActivated
	if (mEntitiesActivated.count(entityId) == 1 &&
	    !mEntitiesActivated[entityId]->isActive())
	  {
	    if (mEntitiesActivated[entityId]->isDestroyed())
	      mEntitiesDestroyed[entityId] = mEntitiesActivated[entityId];
	    else
	      mEntitiesDeactivated[entityId] = mEntitiesActivated[entityId];

	    mEntitiesActivated.erase(entityId);
	  }
      }
//    mEntitiesActivated.clear();
//    mEntitiesDestroyed.clear();
//    mEntitiesDeactivated.clear();
//
//    for (auto &it : mEntities)
//      {
//	auto entity = it.second.get();
//
//	if (entity->isDestroyed())
//	  {
//
//	  }
//      }
//
//    for (auto &it : mEntitiesFiltered)
//      {
//	std::remove_if(std::begin(it.second), std::end(it.second), [](auto &entity) {
//	  return (entity.isDestroyed() || !entity.isActive());
//	});
//
//	for (auto &entityActivated : mEntitiesActivated)
//	  {
//	    if (it.first & entityActivated.getId())
//	      it.second.push_back(entityActivated);
//	  }
//      }
  }

  void EntityManager::onEntityStateChanged(Entity const &entity)
  {
    mEntitiesIdStateChanged.push_back(entity.getId());
  }

}
