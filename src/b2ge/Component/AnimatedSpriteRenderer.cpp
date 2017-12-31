//
// Created by brd6 on 30/12/17.
//

#include <memory>
#include <SFML/System/Time.hpp>
#include "b2ge/Component/AnimatedSpriteRenderer.hpp"

namespace b2ge
{
  AnimatedSpriteRenderer::AnimatedSpriteRenderer() :
  	mPaused(false),
	mLopped(false),
	mCurrentAnimationName(""),
	mFrameTime(0),
	mCurrentTime(0),
	mCurrentFrame(0)
  {
  }

  void AnimatedSpriteRenderer::add(std::string const &name,
			    AnimationPtr animation)
  {
    mAnimations[name] = std::move(animation);
  }

  void AnimatedSpriteRenderer::play(std::string const &name, bool looped)
  {
    if (mAnimations.count(name) <= 0)
      throw std::out_of_range("animation named '" + name + "' not found");

    mCurrentAnimationName = name;
    mLopped = looped;
    mPaused = false;
    mCurrentFrame = 0;

    setFrame(mCurrentFrame);
  }

  void AnimatedSpriteRenderer::setFrameTime(float time)
  {
    mFrameTime = time;
  }

  void AnimatedSpriteRenderer::pause()
  {
    mPaused = true;
  }

  void AnimatedSpriteRenderer::stop()
  {
    mPaused = true;
    mCurrentFrame = 0;
    setFrame(mCurrentFrame);
  }

  void AnimatedSpriteRenderer::setLooped(bool looped)
  {
    mLopped = looped;
  }

  std::string const &AnimatedSpriteRenderer::getCurrentAnimationName() const
  {
    return mCurrentAnimationName;
  }

  void AnimatedSpriteRenderer::setFrame(int frame)
  {
    if (!mCurrentAnimationName.empty())
      {
	sf::IntRect rect = getCurrentAnimation()->getFrame(frame);

	mVertices[0].position = {0.f, 0.f};
	mVertices[1].position = {0.f, static_cast<float>(rect.height)};
	mVertices[2].position = {static_cast<float>(rect.width),
				 static_cast<float>(rect.height)};
	mVertices[3].position = {static_cast<float>(rect.width), 0.f};

	auto left = static_cast<float>(rect.left) + 0.0001f;
	auto right = left + static_cast<float>(rect.width);
	auto top = static_cast<float>(rect.top);
	auto bottom = top + static_cast<float>(rect.height);

	mVertices[0].texCoords = {left, top};
	mVertices[1].texCoords = {left, bottom};
	mVertices[2].texCoords = {right, bottom};
	mVertices[3].texCoords = {right, top};
      }
  }

  AnimatedSpriteRenderer::AnimationPtr AnimatedSpriteRenderer::getCurrentAnimation() const
  {
    return mAnimations.at(mCurrentAnimationName);
  }

  bool AnimatedSpriteRenderer::isPaused() const
  {
    return mPaused;
  }

  bool AnimatedSpriteRenderer::isLopped() const
  {
    return mLopped;
  }

  float AnimatedSpriteRenderer::getFrameTime() const
  {
    return mFrameTime;
  }

  float AnimatedSpriteRenderer::getCurrentTime() const
  {
    return mCurrentTime;
  }

  int AnimatedSpriteRenderer::getCurrentFrame() const
  {
    return mCurrentFrame;
  }

  void AnimatedSpriteRenderer::setCurrentTime(float time)
  {
    mCurrentTime = time;
  }

  unsigned long AnimatedSpriteRenderer::getAnimationSize() const
  {
    return mAnimations.size();
  }

  void AnimatedSpriteRenderer::setCurrentFrame(int frame)
  {
    mCurrentFrame = frame;
  }

  sf::Vertex const *AnimatedSpriteRenderer::getVertices() const
  {
    return mVertices;
  }

  unsigned long AnimatedSpriteRenderer::getCurrentAnimationFrameSize() const
  {
    return getCurrentAnimation()->mFrames.size();
  }

  void AnimatedSpriteRenderer::addTime(float time)
  {
    setCurrentTime(mCurrentTime + time);
  }

  void AnimatedSpriteRenderer::addFrame(int frame)
  {
    setCurrentFrame(mCurrentFrame + frame);
  }
}