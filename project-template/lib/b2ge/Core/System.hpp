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

  class System
  {
   protected:
    friend class SystemManager;

    SystemId mId;

    World *mWorld;

    std::bitset<COMPONENT_BITSET> mComponentRequiredBitset;

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

    EntitiesMap const &getEntities() const;

    virtual void initialize() {}

   public:
    System();

    virtual ~System() = default;

  };
}

#endif //B2GE_SYSTEM_HPP
