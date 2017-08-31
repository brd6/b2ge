//
// Created by brd6 on 30/08/2017.
//

#include <Core/World.hpp>

namespace b2ge
{
    World::World():
        mEntityManager(std::make_unique<EntityManager>()),
        mSystemManager(std::make_unique<SystemManager>())
    {

    }

    EntityManager &World::getEntityManager() const
    {
        return *(mEntityManager.get());
    }

    SystemManager &World::getSystemManager() const
    {
        return *(mSystemManager.get());
    }
}