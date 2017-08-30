//
// Created by brd6 on 29/08/17.
//

#include <Core/Entity.hpp>

namespace b2ge
{
  std::size_t b2ge::Entity::getNextId()
  {
    static std::size_t mNextId;

    return ++mNextId;
  }

  Entity::Entity():
	  Entity("")
  {

  }

  Entity::Entity(std::string const &name):
	  mIsActive(true),
	  mIsDestroyed(false),
	  mId(getNextId()),
	  mName(name)
  {

  }

  void Entity::setActive(bool isActive)
  {
    mIsActive = isActive;
  }

  bool Entity::isActive() const
  {
    return mIsActive;
  }

  void Entity::destroy()
  {
    mIsDestroyed = true;
  }

  bool Entity::isDestroyed() const
  {
    return mIsDestroyed;
  }

  std::size_t Entity::getId() const
  {
    return mId;
  }

  bool Entity::operator==(Entity const &entity) const
  {
    return entity.getId() == this->getId() && entity.mScene == this->mScene;
  }

  bool Entity::operator!=(Entity const &entity) const
  {
    return !operator==(entity);
  }

  Scene &Entity::getScene() const
  {
    return *mScene;
  }

  std::string const &Entity::getName() const
  {
    return mName;
  }

  void Entity::removeAllComponents()
  {
    mComponents.erase(std::begin(mComponents), std::end(mComponents));
    mComponents.clear();
  }
}