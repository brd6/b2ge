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

    mSfText.setFont(font);
  }

  sf::Vector2f Text::getSize() const
  {
    sf::FloatRect rect = mSfText.getGlobalBounds();

    return {rect.width, rect.height};
  }

  Text::Text() :
   mTextSize(18)
  {
  }

  void Text::setText(std::string const &text)
  {
    mSfText.setString(text);
  }

  sf::String const& Text::getText() const
  {
    return mSfText.getString();
  }

  unsigned int Text::getTextSize() const
  {
    return mSfText.getCharacterSize();
  }

  void Text::setTextSize(unsigned int size)
  {
    mSfText.setCharacterSize(size);
  }

  void Text::setTextColor(const sf::Color &color)
  {
    mSfText.setFillColor(color);
  }

  sf::Color const& Text::getTextColor() const
  {
    return mSfText.getFillColor();
  }

  std::string const& Text::getFont() const
  {
    return mFontName;
  }

  void Text::setStyle(sf::Uint32 style)
  {
    mSfText.setStyle(style);
  }

  sf::Uint32 Text::getStyle() const
  {
    return mSfText.getStyle();
  }

  void Text::setScale(sf::Vector2f const &scale)
  {
    mSfText.setScale(scale);
  }

  void Text::setScale(float x, float y)
  {
    mSfText.setScale(x, y);
  }

}