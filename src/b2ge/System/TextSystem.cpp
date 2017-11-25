//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Text.hpp>
#include "b2ge/System/TextSystem.hpp"

namespace b2ge
{
  TextSystem::TextSystem()
  {
    addComponentRequired<Text>();
  }

  void TextSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	auto &text = it.second->getComponent<Text>();

	target.draw(text, states);
      }
  }
}
