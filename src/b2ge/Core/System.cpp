//
// Created by brd6 on 31/08/2017.
//

#include <iostream>
#include <b2ge/Core/System.hpp>
#include <b2ge/Core/World.hpp>

namespace b2ge
{
  EntitiesMap const &System::getEntities() const
  {
    if (mWorld == nullptr)
      throw std::runtime_error("World must be initialise before");

    ComponentFilterGroupId groupId = getComponentFilterGroupId();

    return mWorld->getEntityManager().getByComponentFilterGroupId(groupId);
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
}