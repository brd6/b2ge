//
// Created by brd6 on 03/02/17.
//

#ifndef _COMPONENT_H_
# define _COMPONENT_H_

#include <b2ge/Core/Config.hpp>

namespace b2ge
{
  class Entity;

  class Component
  {
   private:
    friend class Entity;

    Entity *entity;

   public:
    Component() : entity(nullptr) { };

    virtual ~Component() = default;
  };
}

#endif /* !_COMPONENT_H_ */