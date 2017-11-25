//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_TEXT_HPP
#define B2GE_TEXT_HPP

#include <b2ge/Core/Component.hpp>
#include <SFML/Graphics/Text.hpp>

namespace b2ge
{
  class Text :
  	public Component,
	public sf::Text
  {
   public:
    void setFont(const std::string &fontName);
    sf::Vector2f getSize() const;
  };
}

#endif //B2GE_TEXT_HPP
