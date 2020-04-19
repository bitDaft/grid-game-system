
#include <iostream>

#include "cursor.h"
#include "globals.h"

Cursor::Cursor()
    : IUpdatable(2),
      IDrawable(2),
      speed(100.f),
      position(0, 0)
{
  enableInputHandling();
  _reactionMapper->bindActionToReaction<&Cursor::keyDownPressed>(Actions::DOWN);
  _reactionMapper->bindActionToReaction<&Cursor::keyUpPressed>(Actions::UP);
  _reactionMapper->bindActionToReaction<&Cursor::keyLeftPressed>(Actions::LEFT);
  _reactionMapper->bindActionToReaction<&Cursor::keyRightPressed>(Actions::RIGHT);
  _reactionMapper->bindActionToReaction<&Cursor::keyUpReleased>(Actions::UP_RELEASE);
  _reactionMapper->bindActionToReaction<&Cursor::keyDownReleased>(Actions::DOWN_RELEASE);
  _reactionMapper->bindActionToReaction<&Cursor::keyLeftReleased>(Actions::LEFT_RELEASE);
  _reactionMapper->bindActionToReaction<&Cursor::keyRightReleased>(Actions::RIGHT_RELEASE);
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
  sf::Vector2f movement = {
      (isRight - isLeft) * speed * dt.asSeconds(),
      (isDown - isUp) * speed * dt.asSeconds()};
  // std::cout << isRight << " " << isLeft << " " << isUp << " " << isDown << "\n";
  // std::cout << "x : " << position.x << " y : " << position.y << "\n";
  cursor.update(dt);
  position += movement;
  cursor.setPosition(position);
}
void Cursor::draw(const sf::Time &, sf::RenderTexture &tex)
{
  tex.draw(cursor);
}

void Cursor::setPosition(sf::Vector2f pos)
{
  std::cout << pos.x << " " << pos.y << "\n";
  position.x = pos.x;
  position.y = pos.y;
  cursor.setPosition(position);
}
bool Cursor::keyLeftPressed(sf::Event &)
{
  isLeft = 1;
  return false;
}
bool Cursor::keyUpPressed(sf::Event &)
{
  isUp = 1;
  return false;
}
bool Cursor::keyDownPressed(sf::Event &)
{
  isDown = 1;
  return false;
}
bool Cursor::keyRightPressed(sf::Event &)
{
  isRight = 1;
  return false;
}
bool Cursor::keyLeftReleased(sf::Event &)
{
  isLeft = 0;
  return false;
}
bool Cursor::keyUpReleased(sf::Event &)
{
  isUp = 0;
  return false;
}
bool Cursor::keyDownReleased(sf::Event &)
{
  isDown = 0;
  return false;
}
bool Cursor::keyRightReleased(sf::Event &)
{
  isRight = 0;
  return false;
}