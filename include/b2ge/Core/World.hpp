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
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;

   public:
    World() = default;

    virtual ~World() = default;

    void update(float deltaTime);

    EntityManager &getEntityManager() const;

    SystemManager &getSystemManager() const;

    void setEntityManager(EntityManager *entityManager);

    void setSystemManager(SystemManager *systemManager);

//    void reset();
  };
}

#endif //B2GE_WORLD_HPP
