//
// Created by brd6 on 31/08/2017.
//

#ifndef _SYSTEMS_H_
#define _SYSTEMS_H_

#include "Components.hpp"
#include "Core/System.hpp"

class SpriteRenderSystem :
	public b2ge::System
{
 public:
  SpriteRenderSystem()
  {
    addComponentRequired<Sprite>();
  }
};

#endif /* !_SYSTEMS_H_ */