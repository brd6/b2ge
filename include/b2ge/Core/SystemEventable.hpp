//
// Created by brd6 on 02/09/2017.
//

#ifndef _SYSTEMEVENTABLE_H_
#define _SYSTEMEVENTABLE_H_

#include <SFML/Window/Event.hpp>
#include "b2ge/Core/System.hpp"

namespace b2ge
{
  class SystemEventable :
  	public virtual System
  {
   public:
    virtual void processEvents(sf::Event event) = 0;
  };
}

#endif /* !_SYSTEMEVENTABLE_H_ */