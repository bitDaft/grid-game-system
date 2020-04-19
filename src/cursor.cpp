
#include <iostream>

#include "cursor.hpp"
#include "globals.hpp"

Cursor::Cursor()
    : IUpdatable(2),
      IDrawable(2),
      position(0, 0)
{
}
Cursor::~Cursor()
{
}

void Cursor::setAnimation(Animation &anim)
{
  cursor.setAnimation(anim);
  cursor.setAnimationTime(sf::seconds(.5f));
}

void Cursor::update(const sf::Time &dt)
{
  cursor.update(dt);
  // cursor.setPosition(position);
}

void Cursor::draw(const sf::Time &, sf::RenderTexture &tex)
{
  tex.draw(cursor);
}

void Cursor::setPosition(sf::Vector2f pos)
{
  position.x = pos.x;
  position.y = pos.y;
  cursor.setPosition(position);
}
