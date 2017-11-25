//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_BUTTONSYSTEM_HPP
#define B2GE_BUTTONSYSTEM_HPP

#include "b2ge/Component/Button.hpp"
#include "b2ge/Core/SystemEventable.hpp"

namespace b2ge
{
  class ButtonSystem :
   public SystemEventable
  {
   public:
    ButtonSystem();
    void processEvents(sf::Event event) override ;

   private:
    void processEventForEntity(std::shared_ptr<Entity> entity, sf::Event event);
    void callCallableEvent(Button::ButtonEventCallable, sf::Event event, Button &button);
    sf::FloatRect getSpriteRectangleButton(Sprite &sprite) const;
    sf::Vector2f getSpriteSize(Sprite const &sprite) const;
  };
}

#endif //B2GE_BUTTONSYSTEM_HPP
