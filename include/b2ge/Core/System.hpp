//
// Created by bberd on 30/08/2017.
//

#include "World.hpp"
#include "Util/NonCopyable.hpp"

#ifndef B2GE_SYSTEM_HPP
#define B2GE_SYSTEM_HPP

namespace b2ge
{
    class System :
        public NonCopyable
    {
    private:
        World &mWorld;
        EntityManager &mEntityManager;

    public:
        System(World &world, EntityManager &entityManager) : mWorld(world), mEntityManager(entityManager) {};
        virtual ~System() = default;

        virtual void initialize() {};
    };
}

#endif //B2GE_SYSTEM_HPP
