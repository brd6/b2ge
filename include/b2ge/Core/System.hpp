//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_SYSTEM_HPP
#define B2GE_SYSTEM_HPP

#include "Config.hpp"
#include "ClassIdHandler.hpp"

namespace b2ge
{
  class EntityManager;
  class World;

  class System
  {
   private:
    friend class SystemManager;

    SystemId mId{};

    World *mWorld{nullptr};

//   protected:
//    EntityManager &mEntityManager;

   public:
    System() = default;

    virtual ~System() = default;

    virtual void initialize() {}

    SystemId getId() const { return mId; }
  };
}

#endif //B2GE_SYSTEM_HPP
