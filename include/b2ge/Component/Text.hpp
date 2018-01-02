//
// Created by brd6 on 25/11/17.
//

#ifndef B2GE_TEXT_HPP
#define B2GE_TEXT_HPP

#include <b2ge/Core/Component.hpp>
#include <SFML/Graphics/Text.hpp>

namespace b2ge
{
  struct Text :
   public Component
  {
   private:
    sf::Text mSfText;
    unsigned int mTextSize;
    std::string mFontName;

    friend class TextSystem;

   public:
    Text();

    void setFont(const std::string &fontName);
    sf::Vector2f getSize() const;

    void setText(std::string const &text);
    sf::String const &getText() const;

    void setTextSize(unsigned int size);
    unsigned int getTextSize() const;

    void setTextColor(const sf::Color &color);
    sf::Color const &getTextColor() const;

    std::string const &getFont() const;

    void setStyle(sf::Uint32 style);
    sf::Uint32 getStyle() const;
  };
}

#endif //B2GE_TEXT_HPP
