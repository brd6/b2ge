//
// Created by brd6 on 29/08/17.
//

#ifndef _COMPONENTS_H_
# define _COMPONENTS_H_

struct Vector2D : b2ge::Component
{
  float x;
  float y;
};

struct Sprite : b2ge::Component
{
  std::string texturePath;
};

struct Player : b2ge::Component
{
  std::string name;
};

#endif /* !_COMPONENTS_H_ */