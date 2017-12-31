//
// Created by brd6 on 23/11/17.
//

#include <Scene/Gameplay.hpp>
#include "Game.hpp"
#include "Scene/MainScene.hpp"

namespace example
{
    void Game::initialize()
    {
        mSceneManager.add("Main", new MainScene());
        mSceneManager.add("Gameplay", new Gameplay());

//        mSceneManager.setStart("Main")
    }

    void Game::processEvents(sf::Event event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                    Game::getInstance()->quit();
                    break;
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::Closed)
	  Game::getInstance()->quit();
    }
}