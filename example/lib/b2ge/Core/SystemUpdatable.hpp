//
// Created by brd6 on 02/09/2017.
//

#ifndef _SYSTEMUPDATABLE_H_
#define _SYSTEMUPDATABLE_H_

#include <b2ge/Core/System.hpp>

namespace b2ge
{
  class SystemUpdatable :
  	public System
  {
   public:
    virtual void update(float deltaTime) = 0;
  };
}

#endif /* !_SYSTEMUPDATABLE_H_ */