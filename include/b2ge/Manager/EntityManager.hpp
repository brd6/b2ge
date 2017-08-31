//
// Created by brd6 on 30/08/17.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <memory>
#include <unordered_map>
#include "Core/Entity.hpp"

namespace b2ge
{
  class Scene;

  class EntityManager
  {
   private:
    friend class World;

    World *mWorld{nullptr};

    using entityPtr = std::unique_ptr<Entity>;

    std::unordered_map<EntityId, entityPtr> mEntities;

   public:
    EntityManager() = default;

    ~EntityManager() = default;

    EntityManager(EntityManager const &) = delete;

    EntityManager &operator=(EntityManager const &) = delete;

    void add(Entity *entity);

    Entity &get(std::size_t id);

    Entity &get(std::string const &name);

    Entity &createEntity();

    Entity &createEntity(std::string const &name);

   private:
    void removeEntitiesDestroyed();

  };
}

#endif //_ENTITYMANAGER_H_