//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_UIRENDERSYSTEM_HPP
#define B2GE_UIRENDERSYSTEM_HPP

#include "b2ge/Core/SystemDrawable.hpp"

namespace b2ge
{
  class TextSystem :
   public SystemDrawable
  {
   public:
    TextSystem();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  };

}

#endif //B2GE_UIRENDERSYSTEM_HPP
