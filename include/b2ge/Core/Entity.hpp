//
// Created by brd6 on 29/08/17.
//


#ifndef ENTITY_H_
# define ENTITY_H_

#include <bitset>
#include <memory>
#include <vector>
#include <algorithm>
#include "Component.hpp"
#include "Config.hpp"
#include "ClassIdHandler.hpp"

namespace b2ge
{
  class Entity
  {
   private:
    friend class EntityManager;

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

   private:
    EntityId getNextId();

    template<typename TComponent>
    void registerComponent(TComponent *component)
    {
      mComponentArray[getClassTypeId<TComponent>()] = component;
      mComponentBitset[getClassTypeId<TComponent>()] = true;
    }

    template<typename TComponent>
    void unregisterComponent()
    {
      mComponentArray[getClassTypeId<TComponent>()] = nullptr;
      mComponentBitset[getClassTypeId<TComponent>()] = false;
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

      return *component;
    };

    template<typename TComponent>
    TComponent &getComponent() const
    {
      if (!hasComponent<TComponent>())
	throw std::logic_error("Access to a not entity's component");

      auto component(mComponentArray[getClassTypeId<TComponent>()]);
      return *static_cast<TComponent *>(component);
    }

    template<typename TComponent>
    void removeComponent()
    {
      if (!hasComponent<TComponent>())
	throw std::invalid_argument("Access to a not entity's component");

      auto currComponent = mComponentArray[getClassTypeId<TComponent>()];

      auto it = std::find_if(std::begin(mComponents),
			     std::end(mComponents),
			     [currComponent]
				     (std::unique_ptr<Component> const &component) {
			       return component.get() == currComponent;
			     });

      if (it == std::end(mComponents))
	return;

      it->reset();
      mComponents.erase(it);

      unregisterComponent<TComponent>();
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

  };
}

#endif /* !ENTITY_H_ */