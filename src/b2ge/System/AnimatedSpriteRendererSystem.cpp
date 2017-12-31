//
// Created by brd6 on 30/12/17.
//

#include <b2ge/Util.hpp>
#include <b2ge/Component/Sprite.hpp>
#include <b2ge/Component/AnimatedSpriteRenderer.hpp>
#include <b2ge/Component/Transform.hpp>
#include "b2ge/System/AnimatedSpriteRendererSystem.hpp"

namespace b2ge
{
  AnimatedSpriteRendererSystem::AnimatedSpriteRendererSystem()
  {
    addComponentRequired<Transform>();
    addComponentRequired<Sprite>();
    addComponentRequired<AnimatedSpriteRenderer>();
  }

  void AnimatedSpriteRendererSystem::update(float deltaTime)
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processUpdateEntity(it.second, deltaTime);
      }
  }

  void AnimatedSpriteRendererSystem::processUpdateEntity(EntityPtr entity,
							 float deltaTime)
  {
    auto &spriteAnimation = entity->getComponent<AnimatedSpriteRenderer>();

    if (spriteAnimation.isPaused() ||
     	spriteAnimation.getCurrentAnimationName().empty())
      return;

    spriteAnimation.addTime(deltaTime);

    if (spriteAnimation.getCurrentTime() >= spriteAnimation.getFrameTime())
      {
	spriteAnimation.setCurrentTime(0);

	if (spriteAnimation.getCurrentFrame() + 1
	    < static_cast<int>(spriteAnimation.getCurrentAnimationFrameSize()))
	  spriteAnimation.addFrame(1);
	else
	  {
	    spriteAnimation.setCurrentFrame(0);

	    if (!spriteAnimation.isLopped())
	      spriteAnimation.pause();
	  }
	spriteAnimation.setFrame(spriteAnimation.getCurrentFrame());
      }
  }

  void AnimatedSpriteRendererSystem::draw(sf::RenderTarget &target,
					  sf::RenderStates states) const
  {
    auto &entities = getEntities();

    for (auto &it : entities)
      {
	processDrawEntity(it.second, target, states);
      }
  }

  void AnimatedSpriteRendererSystem::processDrawEntity(EntityPtr entity,
						       sf::RenderTarget &target,
						       sf::RenderStates states) const
  {
    auto &sprite = entity->getComponent<Sprite>();
    auto &transform = entity->getComponent<Transform>();
    auto &animatedSpriteRenderer = entity->getComponent<AnimatedSpriteRenderer>();

    states.texture = &sprite.getTexture();
    states.transform *= transform.getTransform();

    target.draw(animatedSpriteRenderer.getVertices(),
		AnimatedSpriteRenderer::VERTICES_SIZE,
		AnimatedSpriteRenderer::VERTEX_TYPE, states);
  }
}