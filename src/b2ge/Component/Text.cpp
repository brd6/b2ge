//
// Created by brd6 on 25/11/17.
//

#include <b2ge/Component/Text.hpp>
#include <b2ge/Manager/ResourceManager.hpp>

namespace b2ge
{
  void Text::setFont(const std::string &fontName)
  {
    auto resourceManager = ResourceManager::getInstance();

    auto &font = resourceManager->getFont(fontName);

    sf::Text::setFont(font);
  }

  sf::Vector2f Text::getSize() const
  {
    sf::FloatRect rect = getGlobalBounds();

    return {rect.width, rect.height};
  }
}