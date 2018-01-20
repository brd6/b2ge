//
// Created by brd6 on 24/11/17.
//

#include <b2ge/Core/Scene.hpp>
#include "b2ge/Core/BaseGame.hpp"

namespace b2ge
{
  BaseGame *game = nullptr;

  BaseGame::BaseGame(std::string const &title, unsigned int width,
		     unsigned int height) :
   TIME_PER_FRAME(sf::seconds(1.f / 60.f)),
   mWidth(width),
   mHeight(height),
   mTitle(title),
   mTimeSinceLastUpdate(sf::Time::Zero),
   running(false)
  {
    game = this;
  }

  void BaseGame::run()
  {
    initialize();
    createWindow();

    running = true;
    while (running)
      {
	runProcessEvents();

	mTimeSinceLastUpdate += mClock.restart();
	while (mTimeSinceLastUpdate > TIME_PER_FRAME)
	  {
	    mTimeSinceLastUpdate -= TIME_PER_FRAME;

	    runProcessEvents();
	    runUpdate(TIME_PER_FRAME.asSeconds());
	  }
	runDraw();
      }
  }

  unsigned int BaseGame::getWidth() const
  {
    return mWidth;
  }

  unsigned int BaseGame::getHeight() const
  {
    return mHeight;
  }

  void BaseGame::createWindow()
  {
    mWindow.create(sf::VideoMode(mWidth, mHeight),
		   mTitle,
		   sf::Style::Titlebar | sf::Style::Close);
  }

  void BaseGame::runProcessEvents()
  {
    sf::Event event{};

    mSceneManager.lock();
    while (mWindow.pollEvent(event))
      {
	processEvents(event);
	mSceneManager.processEvents(event);
      }
    mSceneManager.unlock();
  }

  void BaseGame::runUpdate(float deltaTime)
  {
    mSceneManager.lock();
    mSceneManager.update(deltaTime);
    mSceneManager.unlock();
  }

  void BaseGame::runDraw()
  {
    mSceneManager.lock();

    auto &currentScene = mSceneManager.getCurrent();

    mWindow.clear();
    mWindow.draw(currentScene);
    mWindow.display();

    mSceneManager.unlock();
  }

  void BaseGame::quit()
  {
    running = false;
    mSceneManager.destroy();
  }

  BaseGame *BaseGame::getInstance()
  {
    return game;
  }

  sf::RenderWindow const &BaseGame::getRenderWindow() const
  {
    return mWindow;
  }
}