//
// Created by brd6 on 31/08/2017.
//

#include <iostream>
#include <b2ge/Core/System.hpp>
#include <b2ge/Core/World.hpp>

namespace b2ge
{
  EntitiesVector System::getEntities() const
  {
    if (mWorld == nullptr)
      throw std::runtime_error("World must be initialise before");

//    ComponentFilterGroupId groupId = getComponentFilterGroupId();

//    auto &entitiesTmp = mWorld->getEntityManager().getByComponentFilterGroupId(groupId);

    return mEntities;
  }

  SystemId System::getId() const
  {
    return mId;
  }

  ComponentFilterGroupId System::getComponentFilterGroupId() const
  {
    return mComponentRequiredBitset.to_ulong();
  }

  System::System() :
	mId(0),
	mWorld(nullptr),
	mComponentRequiredBitset(0)
  {

  }

  void System::addEntity(std::shared_ptr<Entity> entity)
  {
    mEntities.push_back(entity);
  }

  void System::removeEntity(std::shared_ptr<Entity> entity)
  {
    auto it = std::find_if(std::begin(mEntities),
			   std::end(mEntities), [&entity](auto &e){
       return entity->getId() == e->getId();
     });

    if (it == std::end(mEntities))
      return;

    mEntities.erase(it);
  }
}