//
// Created by brd6 on 30/08/17.
//

#include <algorithm>
#include <iostream>
#include <b2ge/Manager/EntityManager.hpp>
#include <b2ge/Manager/SystemManager.hpp>

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

    if (it != std::end(mEntitiesActivated))
      return *(it->second);

    it = std::find_if(std::begin(mEntitiesDeactivated), std::end(mEntitiesDeactivated),
		      [name](auto &entity) {
			return (entity.second->getName() == name);
		      });
    if (it != std::end(mEntitiesDeactivated))
      return *(it->second);

    throw std::logic_error("Entity '" + name + "' not found.");
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
    if (mEntitiesFiltered.count(id) == 0)
      throw std::logic_error("Component Filter Group Id not found");

    return mEntitiesFiltered.at(id);
  }

  void EntityManager::update()
  {
    for(auto &entityId : mEntitiesIdStateChanged)
      {
	auto entity = getCorrectEntityForUpdate(entityId);

	if (entity == nullptr)
	  continue;

	applyEntityUpdate(entity);
	applyEntityFilteredRemoved(entity);
	applyEntityFilteredUpdate(entity);
      }
    removeEntitiesDestroyed();
//    removeEntitiesComponentsDestroyed();
    mEntitiesIdStateChanged.clear();
  }

  void EntityManager::onEntityStateChanged(Entity const &entity)
  {
    mEntitiesIdStateChanged.push_back(entity.getId());
  }

  std::vector<ComponentFilterGroupId> const
  EntityManager::getEntityComponentFilterGroupIds(const Entity &entity) const
  {
    std::vector<ComponentFilterGroupId> componentFilterGroupIds;

    for (auto &it : mEntitiesFiltered)
      {
	if (((entity.mComponentBitset.to_ulong() & it.first) == it.first))
	  componentFilterGroupIds.push_back(it.first);
      }

    return componentFilterGroupIds;
  }

  std::vector<ComponentFilterGroupId> const
  EntityManager::getEntityComponentsRemovedFilterGroupIds(const Entity &entity) const
  {
    std::vector<ComponentFilterGroupId> componentFilterGroupIds;

    for (auto &it : mEntitiesFiltered)
      {
	if (((entity.mComponentsRemovedBitset.to_ulong() & it.first) == it.first))
	  componentFilterGroupIds.push_back(it.first);
      }

    return componentFilterGroupIds;
  }

  std::shared_ptr<Entity> EntityManager::getCorrectEntityForUpdate(EntityId entityId)
  {
    decltype(mEntitiesActivated.begin()->second) entity = nullptr;

    if (mEntitiesActivated.count(entityId) == 1)
      {
	entity = mEntitiesActivated.at(entityId);

	mEntitiesActivated.erase(entityId);
      }
    else if (mEntitiesDeactivated.count(entityId) == 1)
      {
	entity = mEntitiesDeactivated.at(entityId);

	mEntitiesDeactivated.erase(entityId);
      }

    return entity;
  }

  void EntityManager::applyEntityUpdate(std::shared_ptr<Entity> &entity)
  {
    if (entity->isDestroyed())
      mEntitiesDestroyed[entity->getId()] = entity;
    else if (!entity->isActive())
      mEntitiesDeactivated[entity->getId()] = entity;
    else
      mEntitiesActivated[entity->getId()] = entity;
  }

  void EntityManager::applyEntityFilteredUpdate(std::shared_ptr<Entity> &entity)
  {
    auto entityComponentFilterGroupId = getEntityComponentFilterGroupIds(*entity);

    for (auto componentFilterGroupId : entityComponentFilterGroupId)
      {
	if (entity->isActive() &&
	 !mEntitiesFiltered[componentFilterGroupId].count(entity->getId()))
	  {
	    mEntitiesFiltered[componentFilterGroupId][entity->getId()] = entity;
	    mSystemManager->addEntity(entity, componentFilterGroupId);
	  }
	else if (!entity->isActive())
	  {
	    mEntitiesFiltered[componentFilterGroupId].erase(entity->getId());
	    mSystemManager->removeEntity(entity, componentFilterGroupId);
	  }
      }
  }

  void EntityManager::applyEntityFilteredRemoved(std::shared_ptr<Entity> &entity)
  {
    if (!entity->hasComponentsRemoved())
      return;
    auto entityComponentFilterGroupId = getEntityComponentsRemovedFilterGroupIds(*entity);

    for (auto componentFilterGroupId : entityComponentFilterGroupId)
      {
	if (mEntitiesFiltered[componentFilterGroupId].count(entity->getId()))
	  {
	    mEntitiesFiltered[componentFilterGroupId].erase(entity->getId());
	    mSystemManager->removeEntity(entity, componentFilterGroupId);
	  }
      }

    removeEntitiesComponentsDestroyed();
  }

  void EntityManager::removeEntitiesDestroyed()
  {
    for (auto &it : mEntitiesDestroyed)
      {
	it.second->removeAllComponents();
      }

    mEntitiesDestroyed.erase(std::begin(mEntitiesDestroyed), std::end(mEntitiesDestroyed));
    mEntitiesDestroyed.clear();
  }

  void EntityManager::registerSystemComponentFilterGroupId(ComponentFilterGroupId id)
  {
    mEntitiesFiltered[id] = {};
  }

  void EntityManager::destroy(Entity &entity)
  {
    entity.destroy();
  }

  void EntityManager::destroy(std::string const &name)
  {
    auto &entity = get(name);

    destroy(entity);
  }

  void EntityManager::destroy(std::size_t id)
  {
    auto &entity = get(id);

    destroy(entity);
  }

  void EntityManager::removeEntitiesComponentsDestroyed()
  {
    for (auto &it : mEntitiesActivated)
      {
	if ((it.second->hasComponentsRemoved()))
	  it.second->clearAllRemovedComponents();
      }
  }
}
