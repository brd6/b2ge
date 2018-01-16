//
// Created by brd6 on 29/08/17.
//


#ifndef ENTITY_H_
# define ENTITY_H_

#include <bitset>
#include <memory>
#include <vector>
#include <algorithm>
#include <array>
#include <b2ge/Core/Component.hpp>
#include <b2ge/Core/ClassIdHandler.hpp>
#include <iostream>

namespace b2ge
{
  class World;

  class Entity
  {
   public:
    using Ptr = std::shared_ptr<b2ge::Entity>;

   private:
    friend class EntityManager;

    World *mWorld;

    bool mIsActive;

    /**
     * Indicate if the entity is destroyed or not.
     * The entity is really destroyed at the next frame
     */
    bool mIsDestroyed;

    using ComponentPtr = std::unique_ptr<Component>;

    std::vector<ComponentPtr> mComponents;

    /**
     * Helper for component access
     */
    std::bitset<COMPONENT_BITSET> mComponentBitset;
    std::array<Component *, COMPONENT_BITSET> mComponentArray;

    EntityId mId;

    std::string mName;

    std::vector<ClassId> mComponentsRemoved;
    std::bitset<COMPONENT_BITSET> mComponentsRemovedBitset;

   private:
    static EntityId getNextId();

    template<typename TComponent>
    void registerComponent(TComponent *component)
    {
      mComponentArray[getClassTypeId<TComponent>()] = component;
      mComponentBitset[getClassTypeId<TComponent>()] = true;
    }

    template<typename TComponent>
    void unregisterComponent()
    {
      unregisterComponent(getClassTypeId<TComponent>());
    }

   public:
    Entity();
    explicit Entity(std::string const &name);

    ~Entity() = default;

    EntityId getId() const;

    void setActive(bool isActive);

    bool isActive() const;

    void destroy();

    bool isDestroyed() const;

    template<typename TComponent, typename... TArgs>
    TComponent &addComponent(TArgs &&... args)
    {
      if (hasComponent<TComponent>())
	throw std::logic_error("Component already exist on this entity");

      TComponent *component(new TComponent(std::forward<TArgs>(args)...));

      component->entity = this;

      std::unique_ptr<Component> componentPtr{component};

      mComponents.emplace_back(std::move(componentPtr));
      registerComponent<TComponent>(component);

      registerEntityStateChanged();

      return *component;
    };

    template<typename TComponent>
    TComponent &getComponent() const
    {
      if (!hasComponent<TComponent>())
	throw std::logic_error("Access to a not entity's component on " + mName);

      auto component(mComponentArray[getClassTypeId<TComponent>()]);
      return *static_cast<TComponent *>(component);
    }

    template<typename TComponent>
    void removeComponent()
    {
      if (!hasComponent<TComponent>())
	throw std::invalid_argument("Access to a not entity's component during remove");

      auto id = getClassTypeId<TComponent>();

      mComponentsRemoved.emplace_back(id);
      mComponentsRemovedBitset[id] = true;

      registerEntityStateChanged();
    }

    void removeAllComponents();

    template<typename TComponent>
    bool hasComponent() const
    {
      return mComponentBitset[getClassTypeId<TComponent>()];
    }

    bool operator==(Entity const &entity) const;

    bool operator!=(Entity const &entity) const;

    std::string const &getName() const;

   private:
    void clearAllRemovedComponents();
    void clearRemovedComponent(ClassId id);

    void unregisterComponent(ClassId i);

    bool hasComponentsRemoved() const;

    void registerEntityStateChanged();
  };
}

#endif /* !ENTITY_H_ */