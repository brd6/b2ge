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

  using EntitiesMap = std::unordered_map<EntityId, std::shared_ptr<Entity>>;

  class EntityManager
  {
   private:
    friend class World;
    friend class Entity;

    World *mWorld{nullptr};

    EntitiesMap mEntitiesActivated;

    EntitiesMap mEntitiesDeactivated;

    EntitiesMap mEntitiesDestroyed;

    std::unordered_map<ComponentFilterGroupId, EntitiesMap> mEntitiesFiltered;

    std::vector<EntityId> mEntitiesIdStateChanged;

   public:
    EntityManager() = default;

    ~EntityManager() = default;

    EntityManager(EntityManager const &) = delete;

    EntityManager &operator=(EntityManager const &) = delete;

    Entity &get(std::size_t id);

    Entity &get(std::string const &name);

    EntitiesMap const &getActivated() const;

    EntitiesMap const &getDeactivated() const;

    EntitiesMap const &getDestroyed() const;

    EntitiesMap const &getByComponentFilterGroupId(ComponentFilterGroupId id) const;

    Entity &create();

    Entity &create(std::string const &name);

   private:
    void onEntityStateChanged(Entity const &entity);

    void removeEntitiesDestroyed();

    void update();
  };
}

#endif //_ENTITYMANAGER_H_