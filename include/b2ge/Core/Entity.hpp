//
// Created by brd6 on 29/08/17.
//


#ifndef ENTITY_H_
# define ENTITY_H_

# include <memory>
# include <vector>
# include <bitset>
# include "Component.hpp"
# include "ComponentIdHandler.hpp"

# include "Config.hpp"

namespace b2ge
{
  class Scene;

  class Entity
  {
   private:
    Scene *mScene;

    // friend class EntityManager;

    bool mIsActive;

    /**
     * Indicate if the entity is destroyed or not.
     * The entity is really destroyed at the next frame
     */
    bool mIsDestroyed;

    using componentPtr = std::unique_ptr<Component>;

    std::vector<componentPtr> mComponents;

    /**
     * Helper for component access
     */
    std::bitset<COMPONENT_BITSET> mComponentBitset;
    std::array<Component*, COMPONENT_BITSET> mComponentArray;

    std::size_t mId;

   private:
    std::size_t getNextId();

    template <typename TComponent>
    void registerComponent(TComponent *component)
    {
      mComponentArray[getComponentTypeId<TComponent>()] = component;
      mComponentBitset[getComponentTypeId<TComponent>()] = true;
    }

   public:
    Entity();
    ~Entity() = default;

    std::size_t getId() const;

    void setActive(bool isActive);
    bool isActive() const;

    void destroy();
    bool isDestroyed() const;

    template <typename TComponent, typename... TArgs>
    TComponent &addComponent(TArgs&&... args)
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

    template <typename TComponent>
    TComponent &getComponent() const
    {
      if (!hasComponent<TComponent>())
	throw std::logic_error("Access to a not entity's component");

      auto component(mComponentArray[getComponentTypeId<TComponent>()]);
      return *static_cast<TComponent *>(component);
    }

    template <typename TComponent>
    bool hasComponent() const
    {
      return mComponentBitset[getComponentTypeId<TComponent>()];
    }

    bool operator==(Entity const &entity) const;
    bool operator!=(Entity const &entity) const;

    Scene &getScene() const;

  };
}

#endif /* !ENTITY_H_ */