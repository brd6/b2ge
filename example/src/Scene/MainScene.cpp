//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Button.hpp>
#include <b2ge/Core/BaseGame.hpp>
#include <b2ge/Component/Sprite.hpp>
#include <b2ge/Component/Text.hpp>
#include <Resources.hpp>
#include "MainScene.hpp"
#include "Game.hpp"

namespace example
{
    void MainScene::create()
    {
        auto &perso = mWorld.getEntityManager().create("perso");

        perso.addComponent<b2ge::Sprite>(Resources::Sprites::player);

        auto &text = mWorld.getEntityManager().create("text");

        auto &textCmp = text.addComponent<b2ge::Text>();
        textCmp.setFont(Resources::Fonts::defaultFont);
        textCmp.setCharacterSize(30);
        textCmp.setStyle(sf::Text::Bold);
        textCmp.setFillColor(sf::Color::Red);
        textCmp.setString("Hello world");
        textCmp.setPosition(42, 42);

        auto &btn = mWorld.getEntityManager().create("btn");

        auto &btnCmp = btn.addComponent<b2ge::Button>();
        auto &btnSpriteCmp = btn.addComponent<b2ge::Sprite>(Resources::Sprites::player);

        btnSpriteCmp.setPosition(200, 100);

        btnCmp.onClickEvent = [&](sf::Event event, b2ge::Button &button) {
            std::cout << "Button click!" << std::endl;
            
            btnSpriteCmp.setPosition(100, 100);
        };

    }

    void MainScene::processEvents(sf::Event event)
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