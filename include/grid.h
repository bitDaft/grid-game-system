#ifndef GRID_HPP
#define GRID_HPP

#include <TE/Game.hpp>
#include <TE/IUpdatable.hpp>
#include <TE/IDrawable.hpp>

#include "cursor.h"

class Grid : public Game, public IUpdatable, public IDrawable
{
public:
  Grid();
  ~Grid();

  void init();
  void update(const sf::Time &);
  void draw(const sf::Time &, sf::RenderTexture &);

private:
  bool mouseLeftDown(sf::Event &);

private:
  sf::Sprite grid;
  Cursor cur;
};

#endif