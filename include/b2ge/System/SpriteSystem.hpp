//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_SPRITERENDERSYSTEM_HPP
#define B2GE_SPRITERENDERSYSTEM_HPP

#include <b2ge/Core/SystemDrawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace b2ge
{
    class SpriteSystem :
        public SystemDrawable
    {
     public:
      SpriteSystem();
      void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif //B2GE_SPRITERENDERSYSTEM_HPP
