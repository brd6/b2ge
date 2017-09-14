//
// Created by brd6 on 03/02/17.
//

#ifndef _CLASSIDHANDLER_H_
# define _CLASSIDHANDLER_H_

#include <b2ge/Core/Config.hpp>

namespace b2ge
{
  inline ClassId generateClassId() noexcept
  {
    static ClassId lastId{0};

    return lastId++;
  }

  template<typename TClass>
  inline ClassId getClassTypeId() noexcept
  {
    static ClassId typeId{generateClassId()};

    return typeId;
  }
}

#endif /* !_CLASSIDHANDLER_H_ */