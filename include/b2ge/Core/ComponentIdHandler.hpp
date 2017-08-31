//
// Created by brd6 on 03/02/17.
//

#ifndef _COMPONENTIDHANDLER_H_
# define _COMPONENTIDHANDLER_H_

namespace b2ge
{
  using ComponentId = std::size_t;

  inline ComponentId getUniqueComponentId() noexcept
  {
    static ComponentId lastId{0};

    return lastId++;
  }

  template<typename TComponent>
  inline ComponentId getComponentTypeId() noexcept
  {
    static ComponentId typeId{getUniqueComponentId()};

    return typeId;
  }
}

#endif /* !_COMPONENTIDHANDLER_H_ */