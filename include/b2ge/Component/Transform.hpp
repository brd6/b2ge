//
// Created by brd6 on 31/12/17.
//

#ifndef B2GE_TRANSFORM_HPP
#define B2GE_TRANSFORM_HPP

#include <b2ge/Core/Component.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace b2ge
{
  class Transform :
  	public Component,
	public sf::Transformable
  {

  };
}

#endif //B2GE_TRANSFORM_HPP
