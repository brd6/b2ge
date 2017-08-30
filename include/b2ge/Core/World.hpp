//
// Created by bberd on 30/08/2017.
//

#ifndef B2GE_WORLD_HPP
#define B2GE_WORLD_HPP

#include <Manager/EntityManager.hpp>

namespace b2ge
{
    class World :
            public NonCopyable
    {
    protected:
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<SystemManager> mSystemManager;

    public:
        World();
        virtual ~World() = default;
        void update(float deltaTime);

        EntityManager &getEntityManager() const;
        SystemManager &getSystemManager() const;
    };
}

#endif //B2GE_WORLD_HPP
