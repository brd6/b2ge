//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_SPRITE_HPP
#define B2GE_SPRITE_HPP

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "b2ge/Core/Component.hpp"

namespace b2ge
{
    class Sprite :
        public Component
    {
    private:
      std::string mTexturePath;
      sf::Sprite mSprite;
      friend class SpriteRendererSystem;

    public:
      explicit Sprite(std::string const &texturePath);
      void setTexturePath(std::string const &texturePath);
      void setTextureRect(sf::IntRect rect);
      sf::Texture const &getTexture() const;
      sf::IntRect getTextureRect() const;
      void setColor(sf::Color const &color);
      sf::Color getColor() const;
      sf::FloatRect getTextureBounds() const;
      sf::Vector2f getSize() const;

     private:
      sf::Sprite const &getSprite() const;

     private:
      sf::Texture &getResourceTexture(const std::string &basic_string);
    };
}

#endif //B2GE_SPRITE_HPP
