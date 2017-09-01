//
// Created by brd6 on 31/08/2017.
//

#include "Core/System.hpp"
#include "Core/World.hpp"

namespace b2ge
{
  Entities const &System::getEntities() const
  {
    if (mWorld == nullptr)
      throw std::runtime_error("World must be initialise before");

    ComponentFilterGroupId groupId = getComponentFilterGroupId();

    return mWorld->getEntityManager().getByComponentFilterGroupId(groupId);
  }
}