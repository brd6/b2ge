//
// Created by brd6 on 25/11/17.
//

#include "b2ge/System/ButtonSystem.hpp"

namespace b2ge
{

  ButtonSystem::ButtonSystem()
  {
    addComponentRequired<Button, Sprite>();
  }

  void ButtonSystem::processEvents(sf::Event event)
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processEventForEntity(it.second, event);
      }
  }

  void ButtonSystem::processEventForEntity(std::shared_ptr<Entity> entity,
					   sf::Event event)
  {
    auto &button = entity->getComponent<Button>();
    auto &sprite = entity->getComponent<Sprite>();

    if (event.type == sf::Event::MouseButtonReleased)
      {
	auto rect = getSpriteRectangleButton(sprite);;
	if (rect.contains(event.mouseButton.x, event.mouseButton.y))
	  {
	    callCallableEvent(button.onClickEvent, event, button);
	  }
      }
    else if (event.type == sf::Event::MouseMoved)
      {
	auto rect = getSpriteRectangleButton(sprite);
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

  sf::FloatRect ButtonSystem::getSpriteRectangleButton(Sprite &sprite) const
  {
    const sf::Vector2f pos = sprite.getPosition();
    const sf::Vector2f size = getSpriteSize(sprite);
    sf::FloatRect rect;

    rect.left = pos.x;
    rect.top = pos.y;
    rect.width = size.x;
    rect.height = size.y;

    return rect;
  }

  sf::Vector2f ButtonSystem::getSpriteSize(Sprite const &sprite) const
  {
    sf::FloatRect rect = sprite.getGlobalBounds();

    return {rect.width, rect.height};
  }
}
