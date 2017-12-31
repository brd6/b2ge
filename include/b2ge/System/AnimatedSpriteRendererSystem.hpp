//
// Created by brd6 on 30/12/17.
//

#ifndef B2GE_SPRITEANIMATIONSYSTEM_HPP
#define B2GE_SPRITEANIMATIONSYSTEM_HPP

#include <b2ge/Core/SystemUpdatable.hpp>
#include <b2ge/Core/SystemDrawable.hpp>

namespace b2ge
{
  class AnimatedSpriteRendererSystem :
  	public b2ge::SystemUpdatable,
  	public b2ge::SystemDrawable
  {
   public:
    using EntityPtr = std::shared_ptr<b2ge::Entity>;

    AnimatedSpriteRendererSystem();
    void update(float deltaTime) override;
    void draw(sf::RenderTarget &target,
	      sf::RenderStates states) const override;

   private:
    void processUpdateEntity(EntityPtr entity, float deltaTime);
    void processDrawEntity(EntityPtr entity, sf::RenderTarget &target,
			   sf::RenderStates states) const;
  };
}

#endif //B2GE_SPRITEANIMATIONSYSTEM_HPP
