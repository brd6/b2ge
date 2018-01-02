//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_SPRITERENDERSYSTEM_HPP
#define B2GE_SPRITERENDERSYSTEM_HPP

#include <b2ge/Core/SystemDrawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace b2ge
{
    class SpriteRendererSystem :
        public SystemDrawable
    {
     public:
      using EntityPtr = std::shared_ptr<Entity>;

     public:
      SpriteRendererSystem();
      void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

     private:
      void processEntity(EntityPtr entity,
			 sf::RenderTarget &target,
			 sf::RenderStates states) const;
      void sortEntities(EntitiesVector &entities) const;
    };
}

#endif //B2GE_SPRITERENDERSYSTEM_HPP
