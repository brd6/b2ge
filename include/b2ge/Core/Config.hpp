//
// Created by brd6 on 03/02/17.
//

#ifndef _CONFIG_H_
# define _CONFIG_H_

#include <cstddef>

namespace b2ge
{
  constexpr int COMPONENT_BITSET = 48;
  using EntityId = std::size_t;
  using ClassId = std::size_t;
  using SystemId = ClassId;
  using SceneId = ClassId;

  //#define COMPONENT_BITSET 48;
}

#endif /* !_CONFIG_H_ */