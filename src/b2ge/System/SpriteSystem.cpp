//
// Created by brd6 on 25/11/17.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include <b2ge/Component/Sprite.hpp>
#include "b2ge/System/SpriteSystem.hpp"

namespace b2ge
{

  void SpriteSystem::draw(sf::RenderTarget &target,
				sf::RenderStates states) const
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	auto &sprite = it.second->getComponent<Sprite>();

	target.draw(sprite, states);
      }
  }

  SpriteSystem::SpriteSystem()
  {
    addComponentRequired<Sprite>();
  }
}
