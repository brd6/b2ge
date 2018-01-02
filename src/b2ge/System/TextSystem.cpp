//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Text.hpp>
#include <b2ge/Component/Transform.hpp>
#include "b2ge/System/TextSystem.hpp"

namespace b2ge
{
  TextSystem::TextSystem()
  {
    addComponentRequired<Text>();
    addComponentRequired<Transform>();
  }

  void TextSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processEntity(it.second, target, states);
      }
  }

  void TextSystem::processEntity(EntityPtr entity,
				 sf::RenderTarget &target,
				 sf::RenderStates states) const
  {
    auto &text = entity->getComponent<Text>();
    auto &transform = entity->getComponent<Transform>();

    states.transform *= transform.getTransform();

    target.draw(text.mSfText, states);
  }
}
