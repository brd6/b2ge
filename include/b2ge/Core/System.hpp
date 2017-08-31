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

  class System
  {
   private:
    friend class SystemManager;
    SystemId mId{};

   protected:
    EntityManager &mEntityManager;

   public:
    explicit System(EntityManager &entityManager) :
	    mEntityManager(entityManager)
    {

    }

    virtual ~System() = default;

    virtual void initialize() {}

    SystemId getId() const { return mId; }
  };
}

#endif //B2GE_SYSTEM_HPP
