//
// Created by brd6 on 31/08/2017.
//

#include "Core/World.hpp"

namespace b2ge
{
  bool SystemManager::has(SystemId id)
  {
    return mSystems.count(id) > 0;
  }
}