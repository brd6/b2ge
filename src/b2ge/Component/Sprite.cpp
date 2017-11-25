//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Manager/ResourceManager.hpp>
#include <iostream>
#include "b2ge/Component/Sprite.hpp"

namespace b2ge
{
    Sprite::Sprite(std::string const &texturePath) :
            mTexturePath(texturePath)
    {
      auto resourceManager = ResourceManager::getInstance();

      setTexture(resourceManager->getTexture(mTexturePath));
    }

  void Sprite::setTexturePath(std::string const &texturePath)
  {
    mTexturePath = texturePath;

    auto resourceManager = ResourceManager::getInstance();

    setTexture(resourceManager->getTexture(mTexturePath));
  }
}
