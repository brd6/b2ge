//
// Created by brd6 on 31/08/2017.
//

#include <b2ge/Manager/SystemManager.hpp>
#include <b2ge/Core/World.hpp>

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
}