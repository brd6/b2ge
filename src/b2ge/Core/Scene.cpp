//
// Created by brd6 on 24/11/17.
//

#include "b2ge/System/TextSystem.hpp"
#include "b2ge/System/SpriteSystem.hpp"
#include "b2ge/Core/Scene.hpp"
#include "b2ge/System/ButtonSystem.hpp"

namespace b2ge
{

  Scene::Scene()
  {
    mWorld.getSystemManager().add<SpriteSystem>();
    mWorld.getSystemManager().add<TextSystem>();
    mWorld.getSystemManager().add<ButtonSystem>();
  }

  void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    mWorld.draw(target, states);
  }

  std::string const &Scene::getName() const
  {
    return mName;
  }

  void Scene::update(float deltaTime)
  {
    mWorld.update(deltaTime);
  }

  void Scene::initialize()
  {
    create();
  }

  void Scene::executeProcessEvents(sf::Event event)
  {
    mWorld.processEvents(event);
    processEvents(event);
  }
}