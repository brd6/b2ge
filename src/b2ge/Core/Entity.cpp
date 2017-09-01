//
// Created by brd6 on 29/08/17.
//

#include "Core/World.hpp"
#include "Core/Entity.hpp"

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
      mWorld->getEntityManager().onEntityStateChanged(*this);

    mIsActive = isActive;
  }

  bool Entity::isActive() const
  {
    return mIsActive;
  }

  void Entity::destroy()
  {
    if (mWorld != nullptr && !mIsDestroyed)
      mWorld->getEntityManager().onEntityStateChanged(*this);

    mIsDestroyed = true;
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
    mComponents.erase(std::begin(mComponents), std::end(mComponents));
    mComponents.clear();

    mComponentArray.fill(nullptr);
    mComponentBitset.reset();
  }
}