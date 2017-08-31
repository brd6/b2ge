//
// Created by brd6 on 03/02/17.
//

#ifndef _COMPONENT_H_
# define _COMPONENT_H_

# include "Util/NonCopyable.hpp"

namespace b2ge
{
  class Entity;

  class Component
  {
   public:
    Entity *entity;

   public:
    Component() = default;

    virtual ~Component() = default;
  };
}

#endif /* !_COMPONENT_H_ */