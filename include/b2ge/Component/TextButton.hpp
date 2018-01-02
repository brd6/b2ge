//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_TEXTBUTTON_HPP
#define B2GE_TEXTBUTTON_HPP

#include <SFML/Window/Event.hpp>
#include <functional>
#include "Sprite.hpp"

namespace b2ge
{
  struct TextButton :
   public Component
  {
   public:
    using ButtonEventCallable = std::function<void(const sf::Event &event,
						   TextButton &self)>;

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
    TextButton();
    ~TextButton() = default;
  };
}

#endif //B2GE_TEXTBUTTON_HPP
