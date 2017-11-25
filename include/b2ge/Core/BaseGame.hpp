//
// Created by brd6 on 24/11/17.
//

#ifndef B2GE_BASEGAME_HPP
#define B2GE_BASEGAME_HPP

#include <SFML/Graphics.hpp>
#include <b2ge/Manager/SceneManager.hpp>

namespace b2ge
{
  class BaseGame
  {
   private:
    const sf::Time TIME_PER_FRAME;
    unsigned int mWidth;
    unsigned int mHeight;
    sf::RenderWindow mWindow;
    std::string mTitle;
    sf::Clock mClock;
    sf::Time mTimeSinceLastUpdate;
    bool running;

   protected:
    SceneManager mSceneManager;

   public:
    static const unsigned int DEFAULT_WIDTH = 800;
    static const unsigned int DEFAULT_HEIGHT = 600;

   public:
    explicit BaseGame(std::string const &title = "Game",
		      unsigned int width = DEFAULT_WIDTH,
		      unsigned int height = DEFAULT_HEIGHT);
    virtual ~BaseGame() = default;

    BaseGame(BaseGame const &) = delete;
    BaseGame &operator=(BaseGame const &) = delete;

    void run();

    void quit();

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    static BaseGame *getInstance();

   protected:
    virtual void initialize() = 0;

   private:
    void createWindow();
    void runProcessEvents();
    void runUpdate(float deltaTime);
    void runDraw();

  };
}

#endif //B2GE_BASEGAME_HPP
