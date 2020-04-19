#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SFML/Window/Event.hpp>

#include <TE/IUpdatable.hpp>
#include <TE/IDrawable.hpp>
#include <TE/AnimatedSprite.hpp>
#include <TE/InputHandler.hpp>

class Cursor : public IUpdatable, public IDrawable
{
public:
  Cursor();
  ~Cursor();

  void setAnimation(Animation &anim);

  void update(const sf::Time &);
  void draw(const sf::Time &, sf::RenderTexture &);

  void setPosition(sf::Vector2f pos);

private:
  AnimatedSprite cursor;
  sf::Vector2f position;
};

#endif