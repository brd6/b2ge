//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Transform.hpp>
#include "b2ge/System/ButtonSystem.hpp"

namespace b2ge
{

  ButtonSystem::ButtonSystem()
  {
    addComponentRequired<Button, Sprite, Transform>();
  }

  void ButtonSystem::processEvents(sf::Event event)
  {
    auto entities = getEntities();

    for (auto &it : entities)
      {
	processEventForEntity(it, event);
      }
  }

  void ButtonSystem::processEventForEntity(std::shared_ptr<Entity> entity,
					   sf::Event event)
  {
    auto &button = entity->getComponent<Button>();
    auto &sprite = entity->getComponent<Sprite>();
    auto &transform = entity->getComponent<Transform>();

    if (event.type == sf::Event::MouseButtonReleased)
      {
	auto rect = getSpriteRectangleButton(sprite, transform);;
	if (rect.contains(event.mouseButton.x, event.mouseButton.y))
	  {
	    callCallableEvent(button.onClickEvent, event, button);
	  }
      }
    else if (event.type == sf::Event::MouseMoved)
      {
	auto rect = getSpriteRectangleButton(sprite, transform);
	auto oldStatus = button.status;
	button.status = Button::Status::None;
	const sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

	if (rect.contains(mousePos))
	  {
	    button.status = Button::Status::Hover;
	  }
	if ((oldStatus == Button::Status::Hover) &&
	 (button.status == Button::Status::Hover))
	  {
	    callCallableEvent(button.onMouseExitEvent, event, button);
	  }
	else if ((oldStatus != Button::Status::Hover) &&
	 (button.status == Button::Status::Hover))
	  {
	    callCallableEvent(button.onMouseEnterEvent, event, button);
	  }
      }
  }

  void ButtonSystem::callCallableEvent(Button::ButtonEventCallable callback, sf::Event event, Button &button)
  {
    if (callback != nullptr)
      callback(event, button);
  }

  sf::FloatRect ButtonSystem::getSpriteRectangleButton(Sprite &sprite, Transform &transform) const
  {
    const sf::Vector2f pos = transform.getPosition();
    const sf::Vector2f size = sprite.getSize();
    sf::FloatRect rect;

    rect.left = pos.x;
    rect.top = pos.y;
    rect.width = size.x;
    rect.height = size.y;

    return rect;
  }
}
