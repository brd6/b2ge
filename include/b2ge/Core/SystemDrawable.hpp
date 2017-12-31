//
// Created by brd6 on 02/09/2017.
//

#ifndef _SYSTEMDRAWABLE_H_
#define _SYSTEMDRAWABLE_H_

#include <SFML/Graphics.hpp>
#include "b2ge/Core/System.hpp"

namespace b2ge
{
  class SystemDrawable:
  	public virtual System
  {
   public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
  };
}

#endif /* !_SYSTEMDRAWABLE_H_ */