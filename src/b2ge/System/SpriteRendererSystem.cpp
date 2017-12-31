//
// Created by brd6 on 25/11/17.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include <b2ge/Component/Sprite.hpp>
#include <b2ge/Component/Transform.hpp>
#include <b2ge/Component/SpriteRenderer.hpp>
#include "b2ge/System/SpriteRendererSystem.hpp"

namespace b2ge
{

  void SpriteRendererSystem::draw(sf::RenderTarget &target,
				sf::RenderStates states) const
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processEntity(it.second, target, states);
      }
  }

  SpriteRendererSystem::SpriteRendererSystem()
  {
    addComponentRequired<Sprite>();
    addComponentRequired<Transform>();
    addComponentRequired<SpriteRenderer>();
  }

  void SpriteRendererSystem::processEntity(EntityPtr entity,
					   sf::RenderTarget &target,
					   sf::RenderStates states) const
  {
    auto &sprite = entity->getComponent<Sprite>();
    auto &transform = entity->getComponent<Transform>();

    states.texture = &sprite.getTexture();
    states.transform *= transform.getTransform();

    target.draw(sprite.getSprite(), states);
  }
}
