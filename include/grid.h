#ifndef GRID_HPP
#define GRID_HPP

#include <TE/Game.hpp>
#include <TE/IUpdatable.hpp>

class Grid : public Game, public IUpdatable
{
public:
  Grid();
  ~Grid();
  void update(const sf::Time &);
  void init();

private:
  bool mouseLeftDown(sf::Event &);
};

#endif