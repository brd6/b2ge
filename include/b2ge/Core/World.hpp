//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_WORLD_HPP
#define B2GE_WORLD_HPP

#include "Manager/EntityManager.hpp"
#include "Manager/SystemManager.hpp"

namespace b2ge
{
  class World
  {
   protected:
    EntityManager mEntityManager;
    SystemManager mSystemManager;

   public:
    World();

    virtual ~World() = default;

    void update(float deltaTime);

    EntityManager &getEntityManager();

    SystemManager &getSystemManager();

//    void reset();
  };
}

#endif //B2GE_WORLD_HPP
