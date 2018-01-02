//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_TextButtonSystem_HPP
#define B2GE_TextButtonSystem_HPP

#include "b2ge/Component/Text.hpp"
#include "b2ge/Component/TextButton.hpp"
#include "b2ge/Core/SystemEventable.hpp"
#include "b2ge/Component/Transform.hpp"

namespace b2ge
{
  class TextButtonSystem :
   public SystemEventable
  {
   public:
    TextButtonSystem();
    void processEvents(sf::Event event) override ;

   private:
    void processEventForEntity(std::shared_ptr<Entity> entity, sf::Event event);
    void callCallableEvent(TextButton::ButtonEventCallable, sf::Event event, TextButton &button);
    sf::FloatRect getSpriteRectangleButton(Text &text, Transform &transform) const;
  };
}

#endif //B2GE_TextButtonSystem_HPP
