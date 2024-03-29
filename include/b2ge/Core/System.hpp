//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_SYSTEM_HPP
#define B2GE_SYSTEM_HPP

#include <bitset>
#include <unordered_map>
#include <b2ge/Core/Config.hpp>
#include <b2ge/Core/ClassIdHandler.hpp>
#include <b2ge/Core/Entity.hpp>

namespace b2ge
{
  class EntityManager;
  class World;

  using ComponentFilterGroupId = unsigned long;
  using EntitiesMap = std::unordered_map<EntityId, std::shared_ptr<Entity>>;
  using EntitiesVector = std::vector<std::shared_ptr<Entity>>;

  class System
  {
   protected:
    friend class SystemManager;

    SystemId mId;

    World *mWorld;

    std::bitset<COMPONENT_BITSET> mComponentRequiredBitset;

    EntitiesVector mEntities;

//   protected:
//    EntityManager &mEntityManager;

   protected:
    template <typename TComponent, typename TComponent2, typename ...TComponents>
    void addComponentRequired()
    {
      addComponentRequired<TComponent>();
      addComponentRequired<TComponent2, TComponents...>();
    }

    template <typename TComponent>
    void addComponentRequired()
    {
      auto componentId = getClassTypeId<TComponent>();

      mComponentRequiredBitset[componentId] = true;
    }

    SystemId getId() const;

    ComponentFilterGroupId getComponentFilterGroupId() const;

    EntitiesVector getEntities() const;

    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(std::shared_ptr<Entity> entity);

   public:
    System();

    virtual ~System() = default;

    virtual void initialize() {}

  };
}

#endif //B2GE_SYSTEM_HPP
