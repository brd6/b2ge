//
// Created by bberd on 30/08/2017.
//

#include <Core/World.hpp>

namespace b2ge
{
    World::World():
        mEntityManager(std::make_unique<EntityManager>())
    {

    }

    EntityManager &World::getEntityManager() const
    {
        return *(mEntityManager.get());
    }
}