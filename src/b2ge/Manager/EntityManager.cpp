//
// Created by brd6 on 30/08/17.
//

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <Manager/EntityManager.hpp>

#include "Core/Entity.hpp"

namespace b2ge
{
  void EntityManager::add(Entity *entity)
  {
    entity->mScene = mScene;

    std::unique_ptr<Entity> entityPtr{entity};

    mEntities[entity->getId()] = std::move(entityPtr);
  }

  Entity &EntityManager::get(std::string const &name)
  {
    auto it = std::find_if(std::begin(mEntities), std::end(mEntities),
			   [name](auto &entity){
			     return (entity.second->getName() == name);
			   });
    if (it == std::end(mEntities))
      throw std::logic_error("Entity '" + name + "' not found.");
    return *((it->second).get());
  }

  Entity &EntityManager::createEntity()
  {
    return createEntity("");
  }

  Entity &EntityManager::createEntity(std::string const &name = "")
  {
    auto *entity = new Entity(name);

    add(entity);

    return *entity;
  }

  void EntityManager::removeEntitiesDestroyed()
  {
    mEntities.erase(
	    std::find_if(std::begin(mEntities), std::end(mEntities),
			 [](auto &entity){
			   return (entity.second->isDestroyed());
			 }),
	    std::end(mEntities)
    );
  }

  void EntityManager::setScene(Scene *scene)
  {
    mScene = scene;
  }

  Scene& EntityManager::getScene()
  {
    return *mScene;
  }

  Entity &EntityManager::get(std::size_t id)
  {
    return *(mEntities[id].get());
  }

}
