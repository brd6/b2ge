//
// Created by brd6 on 30/08/17.
//

#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <memory>
#include <unordered_map>
#include <b2ge/Core/System.hpp>
#include <b2ge/Core/Entity.hpp>

namespace b2ge
{
  class Scene;
  class SystemManager;

  using EntitiesMap = std::unordered_map<EntityId, std::shared_ptr<Entity>>;

  class EntityManager
  {
   private:
    friend class World;
    friend class Entity;
    friend class SystemManager;

    World *mWorld{nullptr};
    SystemManager *mSystemManager{nullptr};

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

    void destroy(Entity &entity);
    void destroy(std::string const &name);
    void destroy(std::size_t id);

   private:
    void onEntityStateChanged(Entity const &entity);

    void update();

    std::shared_ptr<Entity> getCorrectEntityForUpdate(EntityId entityId);

    void applyEntityUpdate(std::shared_ptr<Entity> &entity);

    void applyEntityFilteredUpdate(std::shared_ptr<Entity> &entity);

    std::vector<ComponentFilterGroupId> const getEntityComponentFilterGroupIds(Entity const &entity) const;

    void removeEntitiesDestroyed();

    void registerSystemComponentFilterGroupId(ComponentFilterGroupId id);
  };
}

#endif //_ENTITYMANAGER_H_