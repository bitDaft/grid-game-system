#ifndef GRID_HPP
#define GRID_HPP

#include <TE/Game.hpp>
#include <TE/IUpdatable.hpp>
#include <TE/IDrawable.hpp>

#include "cursor.hpp"

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

  int rows;
  int rowsWidth;
  int cols;
  int colsWidth;


  sf::Sprite grid;
  Cursor cur;
  sf::Vector2f gridPosition;
  sf::Vector2f previousGridPosition;
  sf::Vector2f currentGridPosition;
  sf::Vector2f cursorPosition;
  sf::Time inputTimerBlockCounter;
  bool readyToTakeInput;
};

#endif