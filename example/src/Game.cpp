//
// Created by brd6 on 23/11/17.
//

#include "../include/Game.hpp"
#include "../include/MainScene.hpp"

namespace example
{
    void Game::initialize()
    {
        mSceneManager.add("Main", new MainScene());

//        mSceneManager.setStart()
    }
}