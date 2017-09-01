//
// Created by brd6 on 30/08/2017.
//

#ifndef B2GE_SYSTEM_HPP
#define B2GE_SYSTEM_HPP

#include <bitset>
#include <unordered_map>
#include "Config.hpp"
#include "ClassIdHandler.hpp"
#include "Entity.hpp"

namespace b2ge
{
  class EntityManager;
  class World;

  using ComponentFilterGroupId = unsigned long;
  using EntitiesMap = std::unordered_map<EntityId, std::shared_ptr<Entity>>;

  class System
  {
   private:
    friend class SystemManager;

    SystemId mId{};

    World *mWorld{nullptr};

    std::bitset<COMPONENT_BITSET> mComponentRequiredBitset{};

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

   public:
    System() = default;

    virtual ~System() = default;

    virtual void initialize() {}

    SystemId getId() const { return mId; }

    ComponentFilterGroupId getComponentFilterGroupId() const
    {
      return mComponentRequiredBitset.to_ulong();
    }

    EntitiesMap const &getEntities() const;

  };
}

#endif //B2GE_SYSTEM_HPP
