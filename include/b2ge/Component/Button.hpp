//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_BUTTON_HPP
#define B2GE_BUTTON_HPP

#include <SFML/Window/Event.hpp>
#include <functional>
#include "Sprite.hpp"

namespace b2ge
{
  struct Button :
  	public Component
  {
   public:
    using ButtonEventCallable = std::function<void (const sf::Event &event, Button &self)>;

    ButtonEventCallable onClickEvent;
    ButtonEventCallable onMouseEnterEvent;
    ButtonEventCallable onMouseExitEvent;

    enum Status
    {
      None = 0,
      Hover = 1
    };

    Status status;

   public:
    Button();
    ~Button() = default;
  };
}

#endif //B2GE_BUTTON_HPP
