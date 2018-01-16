//
// Created by brd6 on 29/08/17.
//

#include <b2ge/Core/World.hpp>
#include <b2ge/Core/Entity.hpp>

namespace b2ge
{
  EntityId b2ge::Entity::getNextId()
  {
    static EntityId mNextId;

    return ++mNextId;
  }

  Entity::Entity() :
  	Entity("")
  {

  }

  Entity::Entity(std::string const &name = "") :
	  mIsActive(true),
	  mIsDestroyed(false),
	  mId(getNextId()),
	  mName(name)
  {
  }

  void Entity::setActive(bool isActive)
  {
    if (mWorld != nullptr && mIsActive != isActive)
    {
      mIsActive = isActive;
      mWorld->getEntityManager().onEntityStateChanged(*this);
    }
  }

  bool Entity::isActive() const
  {
    return mIsActive;
  }

  void Entity::destroy()
  {
    if (mWorld != nullptr && !mIsDestroyed)
    {
      mIsDestroyed = true;
      mWorld->getEntityManager().onEntityStateChanged(*this);
    }
  }

  bool Entity::isDestroyed() const
  {
    return mIsDestroyed;
  }

  EntityId Entity::getId() const
  {
    return mId;
  }

  bool Entity::operator==(Entity const &entity) const
  {
    return entity.getId() == this->getId();
  }

  bool Entity::operator!=(Entity const &entity) const
  {
    return !operator==(entity);
  }

  std::string const &Entity::getName() const
  {
    return mName;
  }

  void Entity::removeAllComponents()
  {
//    for (auto &it : mComponents)
//      {
//      }
    mComponents.erase(std::begin(mComponents), std::end(mComponents));
    mComponents.clear();

    mComponentArray.fill(nullptr);
    mComponentBitset.reset();
  }

  void Entity::clearAllRemovedComponents()
  {
    for (auto &it : mComponentsRemoved)
      {
	clearRemovedComponent(it);
      }
    mComponentsRemoved.clear();
    mComponentsRemovedBitset.reset();
  }

  void Entity::clearRemovedComponent(ClassId id)
  {
    auto currComponent =  mComponentArray[id];

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
    unregisterComponent(id);
  }

  void Entity::unregisterComponent(ClassId id)
  {
    mComponentArray[id] = nullptr;
    mComponentBitset[id] = false;
  }

  bool Entity::hasComponentsRemoved() const
  {
    return !mComponentsRemoved.empty();
  }

  void Entity::registerEntityStateChanged()
  {
    mWorld->getEntityManager().onEntityStateChanged(*this);
  }

}