//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Manager/ResourceManager.hpp>
#include <iostream>
#include "b2ge/Component/Sprite.hpp"

namespace b2ge
{
    Sprite::Sprite(std::string const &texturePath)
    {
      setTexturePath(texturePath);
    }

  void Sprite::setTexturePath(std::string const &texturePath)
  {
    mTexturePath = texturePath;

    mSprite.setTexture(getResourceTexture(mTexturePath));
  }

  void Sprite::setTextureRect(sf::IntRect rect)
  {
   mSprite.setTextureRect(rect);
  }

  sf::Texture const &Sprite::getTexture() const
  {
    auto resourceManager = ResourceManager::getInstance();

    return resourceManager->getTexture(mTexturePath);
  }

  sf::IntRect Sprite::getTextureRect() const
  {
    return getSprite().getTextureRect();
  }

  void Sprite::setColor(sf::Color const &color)
  {
    mSprite.setColor(color);
  }

  sf::Color Sprite::getColor() const
  {
    return getSprite().getColor();
  }

  sf::FloatRect Sprite::getTextureBounds() const
  {
    return {{}, getSize()};
  }

  sf::Vector2f Sprite::getSize() const
  {
    return {static_cast<float>(getSprite().getTextureRect().width),
	    static_cast<float>(getSprite().getTextureRect().height)};
  }

  sf::Texture &Sprite::getResourceTexture(const std::string &path)
  {
    auto resourceManager = ResourceManager::getInstance();

    return resourceManager->getTexture(mTexturePath);
  }

  sf::Sprite const &Sprite::getSprite() const
  {
    return mSprite;
  }
}
