//
// Created by brd6 on 25/11/17.
//

#ifndef EXAMPLE_MAINSCENE_HPP
#define EXAMPLE_MAINSCENE_HPP


#include <b2ge/Core/Scene.hpp>

namespace example
{
    class MainScene :
            public b2ge::Scene
    {
    public:
        void create() override;

        void processEvents(sf::Event event) override;
    };
}

#endif //EXAMPLE_MAINSCENE_HPP
