//
// Created by brd6 on 24/11/17.
//

#include <b2ge/System/AnimatedSpriteRendererSystem.hpp>
#include <b2ge/System/TextButtonSystem.hpp>
#include "b2ge/System/TextSystem.hpp"
#include "b2ge/System/SpriteRendererSystem.hpp"
#include "b2ge/Core/Scene.hpp"
#include "b2ge/System/ButtonSystem.hpp"

namespace b2ge
{
  Scene::Scene() :
   mIsInitialized(false)
  {
    mWorld.getSystemManager().add<SpriteRendererSystem>();
    mWorld.getSystemManager().add<TextSystem>();
    mWorld.getSystemManager().add<ButtonSystem>();
    mWorld.getSystemManager().add<TextButtonSystem>();
    mWorld.getSystemManager().add<AnimatedSpriteRendererSystem>();
  }

  void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    mWorld.draw(target, states);
  }

  std::string const &Scene::getName() const
  {
    return mName;
  }

  void Scene::initialize()
  {
    if (mIsInitialized)
      return;

    create();
    mIsInitialized = true;
  }

  void Scene::executeProcessEvents(sf::Event event)
  {
    mWorld.processEvents(event);
    processEvents(event);
  }

  void Scene::executeUpdate(float deltaTime)
  {
    mWorld.update(deltaTime);
    update(deltaTime);
  }
}