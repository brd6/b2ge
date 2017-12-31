//
// Created by brd6 on 25/11/17.
//

#ifndef EXAMPLE_GAMEPLAY_HPP
#define EXAMPLE_GAMEPLAY_HPP

#include <b2ge/Core/Scene.hpp>

namespace example
{
    class Gameplay :
        public b2ge::Scene
    {
    public:
        void create() override;
    };
}

#endif //EXAMPLE_GAMEPLAY_HPP
