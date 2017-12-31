//
// Created by brd6 on 29/12/17.
//

#ifndef B2GE_SPRITEANIMATION_HPP
#define B2GE_SPRITEANIMATION_HPP

#include <memory>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <b2ge/Core/Component.hpp>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

namespace b2ge
{
  struct AnimatedSpriteRenderer :
   public b2ge::Component
  {
    struct Animation
    {
      using Frames = std::vector<sf::IntRect>;

      Animation *addFrame(sf::IntRect frame)
      {
	mFrames.push_back(frame);

	return this;
      }

      sf::IntRect getFrame(int index) const
      {
	return mFrames[index];
      }

     private:
      Frames mFrames;
      friend class AnimatedSpriteRenderer;
    };

    using AnimationPtr = std::shared_ptr<Animation>;
    static const int VERTICES_SIZE = 4;
    static const sf::PrimitiveType VERTEX_TYPE = sf::Quads;

    AnimatedSpriteRenderer();

    void play(std::string const &name, bool looped = true);
    void pause();
    void stop();
    void setLooped(bool looped);
    void add(std::string const &name, AnimationPtr animation);
    void setFrameTime(float time);
    std::string const &getCurrentAnimationName() const;
    bool isPaused() const;
    bool isLopped() const;
    float getFrameTime() const;
    float getCurrentTime() const;
    int getCurrentFrame() const;
    unsigned long getAnimationSize() const;
    unsigned long getCurrentAnimationFrameSize() const;

   private:
    AnimationPtr getCurrentAnimation() const;
    void setFrame(int frame);
    void setCurrentTime(float time);
    void addTime(float time);
    void setCurrentFrame(int frame);
    void addFrame(int frame);

    sf::Vertex const *getVertices() const;
    friend class AnimatedSpriteRendererSystem;

   private:
    std::unordered_map<std::string, AnimationPtr> mAnimations;
    sf::Vertex mVertices[VERTICES_SIZE];
    bool mPaused;
    bool mLopped;
    std::string mCurrentAnimationName;
    float mFrameTime;
    float mCurrentTime;
    int mCurrentFrame;
  };

}

#endif //B2GE_SPRITEANIMATION_HPP
