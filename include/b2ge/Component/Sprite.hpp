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
        public Component,
        public sf::Sprite
    {
    private:
      std::string mTexturePath;

    public:
      explicit Sprite(std::string const &texturePath);
      void setTexturePath(std::string const &texturePath);

    };
}

#endif //B2GE_SPRITE_HPP
