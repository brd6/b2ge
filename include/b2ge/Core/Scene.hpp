//
// Created by brd6 on 24/11/17.
//

#ifndef B2GE_SCENE_HPP
#define B2GE_SCENE_HPP

#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include "World.hpp"

namespace b2ge
{
    class Scene :
            public sf::Drawable
    {
     protected:
      std::string mName;
      World mWorld;
      //      SceneId mId;
      friend class SceneManager;

     public:
      using Ptr = std::unique_ptr<Scene>();

    public:
      Scene();
      ~Scene() override = default;

      Scene(Scene const &) = delete;
      Scene &operator=(Scene const &) = delete;

      std::string const &getName() const;

      void initialize();

      void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
      void update(float deltaTime);
      virtual void processEvents(sf::Event event) {};

      virtual void create() = 0;
      virtual void destroy() {};

     private:
      void executeProcessEvents(sf::Event event);
    };
}

#endif //B2GE_SCENE_HPP
