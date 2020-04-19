#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SFML/Window/Event.hpp>

#include <TE/IUpdatable.hpp>
#include <TE/IDrawable.hpp>
#include <TE/AnimatedSprite.hpp>
#include <TE/InputHandler.hpp>

class Cursor : public InputHandler, public IUpdatable, public IDrawable
{
public:
  Cursor();
  ~Cursor();

  void setAnimation(Animation &anim);

  void update(const sf::Time &);
  void draw(const sf::Time &, sf::RenderTexture &);

  void setPosition(sf::Vector2f pos);

private:
  bool keyLeftPressed(sf::Event &);
  bool keyUpPressed(sf::Event &);
  bool keyDownPressed(sf::Event &);
  bool keyRightPressed(sf::Event &);
  bool keyLeftReleased(sf::Event &);
  bool keyUpReleased(sf::Event &);
  bool keyDownReleased(sf::Event &);
  bool keyRightReleased(sf::Event &);

private:
  int isLeft;
  int isRight;
  int isUp;
  int isDown;

  float speed;

  AnimatedSprite cursor;
  sf::Vector2f position;
};

#endif