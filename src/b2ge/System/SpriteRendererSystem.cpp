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
    auto entities = getEntities();

    sortEntities(entities);

    for (auto &it : entities)
      {
	processEntity(it, target, states);
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

  void SpriteRendererSystem::sortEntities(EntitiesVector &entities) const
  {
    std::sort(std::begin(entities),
	      std::end(entities),
	      [=](std::shared_ptr<Entity> &left,
		  std::shared_ptr<Entity> &right) {
		return left->getComponent<Transform>().drawOrder <
			right->getComponent<Transform>().drawOrder ? 1 : 0;
    });

  }
}
