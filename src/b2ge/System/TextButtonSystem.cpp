//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Transform.hpp>
#include <b2ge/Component/Text.hpp>
#include <b2ge/Component/TextButton.hpp>
#include "b2ge/System/TextButtonSystem.hpp"

namespace b2ge
{

  TextButtonSystem::TextButtonSystem()
  {
    addComponentRequired<TextButton, Text, Transform>();
  }

  void TextButtonSystem::processEvents(sf::Event event)
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processEventForEntity(it.second, event);
      }
  }

  void TextButtonSystem::processEventForEntity(std::shared_ptr<Entity> entity,
					   sf::Event event)
  {
    auto &button = entity->getComponent<TextButton>();
    auto &text = entity->getComponent<Text>();
    auto &transform = entity->getComponent<Transform>();

    if (event.type == sf::Event::MouseButtonReleased)
      {
	auto rect = getSpriteRectangleButton(text, transform);;
	if (rect.contains(event.mouseButton.x, event.mouseButton.y))
	  {
	    callCallableEvent(button.onClickEvent, event, button);
	  }
      }
    else if (event.type == sf::Event::MouseMoved)
      {
	auto rect = getSpriteRectangleButton(text, transform);
	auto oldStatus = button.status;
	button.status = TextButton::Status::None;
	const sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

	if (rect.contains(mousePos))
	  {
	    button.status = TextButton::Status::Hover;
	  }
	if ((oldStatus == TextButton::Status::Hover) &&
	 (button.status == TextButton::Status::Hover))
	  {
	    callCallableEvent(button.onMouseExitEvent, event, button);
	  }
	else if ((oldStatus != TextButton::Status::Hover) &&
	 (button.status == TextButton::Status::Hover))
	  {
	    callCallableEvent(button.onMouseEnterEvent, event, button);
	  }
      }
  }

  void TextButtonSystem::callCallableEvent(TextButton::ButtonEventCallable callback, sf::Event event, TextButton &button)
  {
    if (callback != nullptr)
      callback(event, button);
  }

  sf::FloatRect TextButtonSystem::getSpriteRectangleButton(Text &text, Transform &transform) const
  {
    const sf::Vector2f pos = transform.getPosition();
    const sf::Vector2f size = text.getSize();
    sf::FloatRect rect;

    rect.left = pos.x;
    rect.top = pos.y;
    rect.width = size.x;
    rect.height = size.y;

    return rect;
  }
}
