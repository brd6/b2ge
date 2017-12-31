//
// Created by brd6 on 23/11/17.
//

#ifndef EXAMPLE_GAME_HPP
#define EXAMPLE_GAME_HPP

#include <b2ge/Core/BaseGame.hpp>

namespace example
{
    class Game :
        public b2ge::BaseGame
    {
    protected:
        void initialize() override;

        void processEvents(sf::Event event) override;
    };
}

#endif //EXAMPLE_GAME_HPP
