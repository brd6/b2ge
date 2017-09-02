//
// Created by brd6 on 31/08/2017.
//

#include "Manager/SystemManager.hpp"
#include "Core/World.hpp"

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
}