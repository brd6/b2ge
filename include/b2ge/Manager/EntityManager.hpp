//
// Created by brd6 on 30/08/17.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <memory>
#include <unordered_map>
#include "Core/System.hpp"
#include "Core/Entity.hpp"

namespace b2ge
{
  class Scene;

  using Entities = std::vector<Entity>;
  using entityPtr = std::unique_ptr<Entity>;

  class EntityManager
  {
   private:
    friend class World;

    World *mWorld{nullptr};

    std::unordered_map<EntityId, entityPtr> mEntities;

    Entities mEntitiesActivated;

    Entities mEntitiesDeactivated;

    Entities mEntitiesDestroyed;

    std::unordered_map<ComponentFilterGroupId, Entities> mEntitiesFiltered;

   public:
    EntityManager() = default;

    ~EntityManager() = default;

    EntityManager(EntityManager const &) = delete;

    EntityManager &operator=(EntityManager const &) = delete;

    void add(Entity *entity);

    Entity &get(std::size_t id);

    Entity &get(std::string const &name);

    Entities const &getActivated() const;

    Entities const &getDeactivated() const;

    Entities const &getDestroyed() const;

    Entities const &getByComponentFilterGroupId(ComponentFilterGroupId id) const;

    Entity &create();

    Entity &create(std::string const &name);

   private:
    void removeEntitiesDestroyed();

    void update();
  };
}

#endif //_ENTITYMANAGER_H_