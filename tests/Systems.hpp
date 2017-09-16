//
// Created by brd6 on 31/08/2017.
//

#ifndef _SYSTEMS_H_
#define _SYSTEMS_H_

#include <b2ge/Core/System.hpp>
#include "Components.hpp"

class SpriteRenderSystem :
	public b2ge::System
{
 public:
  SpriteRenderSystem()
  {
    addComponentRequired<Sprite>();
  }

  bool itsWork()
  {
    return true;
  }

  void render()
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	std::cout << "render Entity#" << it.second->getId() << std::endl;
      }
  }

  std::size_t getEntitiesSize()
  {
    return getEntities().size();
  }

};

class CollisionSystem :
	public b2ge::System
{
 public:
  CollisionSystem()
  {
    addComponentRequired<Sprite, Player>();
  }

  std::size_t getEntitiesSize()
  {
    return getEntities().size();
  }

};

#endif /* !_SYSTEMS_H_ */