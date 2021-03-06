
#include <iostream>

#include <TE/ResourceManager.hpp>

#include "globals.hpp"
#include "grid.hpp"

#define inputHoldTime (sf::seconds(.125f))

void generateGridTexture(int, int, int, int);
void loadCursorAnimation();

Grid::Grid()
    : Game(640, 480, "Grid demo"),
      IUpdatable(1),
      IDrawable(1),
      rows(20),
      rowsWidth(21),
      cols(20),
      colsWidth(21),
      grid(),
      cur(),
      gridPosition(0, 0),
      previousGridPosition(0, 0),
      currentGridPosition(0, 0),
      cursorPosition(-20, -20),
      inputTimerBlockCounter(sf::Time::Zero),
      readyToTakeInput(true)
{
  _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyPressed, Actions::UP);
  _aMapper.bindInputToAction(sf::Keyboard::Up, sf::Event::KeyReleased, Actions::UP_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyPressed, Actions::DOWN);
  _aMapper.bindInputToAction(sf::Keyboard::Down, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyPressed, Actions::LEFT);
  _aMapper.bindInputToAction(sf::Keyboard::Left, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyPressed, Actions::RIGHT);
  _aMapper.bindInputToAction(sf::Keyboard::Right, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyPressed, Actions::UP);
  _aMapper.bindInputToAction(sf::Keyboard::W, sf::Event::KeyReleased, Actions::UP_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyPressed, Actions::DOWN);
  _aMapper.bindInputToAction(sf::Keyboard::S, sf::Event::KeyReleased, Actions::DOWN_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyPressed, Actions::LEFT);
  _aMapper.bindInputToAction(sf::Keyboard::A, sf::Event::KeyReleased, Actions::LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyPressed, Actions::RIGHT);
  _aMapper.bindInputToAction(sf::Keyboard::D, sf::Event::KeyReleased, Actions::RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Keyboard::Escape, sf::Event::KeyPressed, Actions::QUIT);

  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonPressed, Actions::MOUSE_LEFT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Left, sf::Event::MouseButtonReleased, Actions::MOUSE_LEFT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonPressed, Actions::MOUSE_RIGHT);
  _aMapper.bindInputToAction(sf::Mouse::Button::Right, sf::Event::MouseButtonReleased, Actions::MOUSE_RIGHT_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonPressed, Actions::MOUSE_MIDDLE);
  _aMapper.bindInputToAction(sf::Mouse::Button::Middle, sf::Event::MouseButtonReleased, Actions::MOUSE_MIDDLE_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonPressed, Actions::MOUSE_X1);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton1, sf::Event::MouseButtonReleased, Actions::MOUSE_X1_RELEASE);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonPressed, Actions::MOUSE_X2);
  _aMapper.bindInputToAction(sf::Mouse::Button::XButton2, sf::Event::MouseButtonReleased, Actions::MOUSE_X2_RELEASE);
  _aMapper.bindInputToAction(sf::Event::MouseMoved, Actions::MOUSE_MOVED);
  _aMapper.bindInputToAction(sf::Event::MouseWheelScrolled, Actions::MOUSE_SCROLL);

  generateGridTexture(rows, cols, rowsWidth, colsWidth);
  loadCursorAnimation();
}
Grid::~Grid()
{
}
void Grid::update(const sf::Time &dt)
{
  if (!readyToTakeInput)
  {
    inputTimerBlockCounter += dt;
    if (
        (!isRight && !isLeft && !isUp && !isDown) ||
        (inputTimerBlockCounter > inputHoldTime))
    {
      inputTimerBlockCounter = sf::Time::Zero;
      readyToTakeInput = true;
    }
  }
  if (readyToTakeInput)
  {
    if (isRight && currentGridPosition.x < rows - 1)
    {
      currentGridPosition.x += 1;
      readyToTakeInput = false;
    }
    if (isLeft && currentGridPosition.x > 0)
    {
      currentGridPosition.x -= 1;
      readyToTakeInput = false;
    }
    if (isDown && currentGridPosition.y < cols - 1)
    {
      currentGridPosition.y += 1;
      readyToTakeInput = false;
    }
    if (isUp && currentGridPosition.y > 0)
    {
      currentGridPosition.y -= 1;
      readyToTakeInput = false;
    }
    if (previousGridPosition.x != currentGridPosition.x ||
        previousGridPosition.y != currentGridPosition.y)
    {
      previousGridPosition = currentGridPosition;
      cursorPosition.x = (gridPosition.x + (currentGridPosition.x * rowsWidth)) + 1;
      cursorPosition.y = (gridPosition.y + (currentGridPosition.y * colsWidth)) + 1;
      cur.setPosition(cursorPosition);
    }
  }
}
void Grid::draw(const sf::Time &, sf::RenderTexture &tex)
{
  tex.draw(grid);
}
void Grid::init()
{
  _reactionMapper->bindActionToReaction<&Game::quit>(Actions::QUIT);
  _reactionMapper->bindActionToReaction<&Grid::mouseLeftDown>(Actions::MOUSE_LEFT);
  _reactionMapper->bindActionToReaction<&Grid::keyDownPressed>(Actions::DOWN);
  _reactionMapper->bindActionToReaction<&Grid::keyUpPressed>(Actions::UP);
  _reactionMapper->bindActionToReaction<&Grid::keyLeftPressed>(Actions::LEFT);
  _reactionMapper->bindActionToReaction<&Grid::keyRightPressed>(Actions::RIGHT);
  _reactionMapper->bindActionToReaction<&Grid::keyUpReleased>(Actions::UP_RELEASE);
  _reactionMapper->bindActionToReaction<&Grid::keyDownReleased>(Actions::DOWN_RELEASE);
  _reactionMapper->bindActionToReaction<&Grid::keyLeftReleased>(Actions::LEFT_RELEASE);
  _reactionMapper->bindActionToReaction<&Grid::keyRightReleased>(Actions::RIGHT_RELEASE);

  grid.setTexture(ResourceManager::getTexture(10));
  float startX = (gameWindow.getSize().x / 2) - ((rows * rowsWidth) / 2);
  float startY = (gameWindow.getSize().y / 2) - ((cols * colsWidth) / 2);
  grid.setPosition(startX, startY);
  cur.setAnimation(ResourceManager::getAnimation(11));
  currentGridPosition.x = 0;
  currentGridPosition.y = 0;
  previousGridPosition.x = 0;
  previousGridPosition.y = 0;
  gridPosition.x = startX;
  gridPosition.y = startY;
  cursorPosition.x = startX + 1;
  cursorPosition.y = startY + 1;
  cur.setPosition(cursorPosition);
}

bool Grid::mouseLeftDown(sf::Event &)
{
  std::cout << "Pressed left\n";
  return false;
}

bool Grid::keyLeftPressed(sf::Event &)
{
  isLeft = 1;
  return false;
}
bool Grid::keyUpPressed(sf::Event &)
{
  isUp = 1;
  return false;
}
bool Grid::keyDownPressed(sf::Event &)
{
  isDown = 1;
  return false;
}
bool Grid::keyRightPressed(sf::Event &)
{
  isRight = 1;
  return false;
}
bool Grid::keyLeftReleased(sf::Event &)
{
  isLeft = 0;
  return false;
}
bool Grid::keyUpReleased(sf::Event &)
{
  isUp = 0;
  return false;
}
bool Grid::keyDownReleased(sf::Event &)
{
  isDown = 0;
  return false;
}
bool Grid::keyRightReleased(sf::Event &)
{
  isRight = 0;
  return false;
}

void generateGridTexture(
    int rows,
    int cols,
    int rowWidth,
    int colWidth)
{

  sf::Image gridImage;
  gridImage.create(cols * colWidth, rows * rowWidth); // currently this is static fixed. will be made dynamic later.

  for (int i = 0; i < rows * rowWidth; i++)
  {
    for (int j = 0; j < cols * colWidth; j++)
    {
      if (
          i % rowWidth == 0 ||
          j % colWidth == 0 ||
          i == (rows * rowWidth - 1) ||
          j == (cols * colWidth - 1))
      {
        gridImage.setPixel(i, j, sf::Color(50, 50, 50, 255));
      }
    }
  }

  sf::Texture gridTex;
  gridTex.loadFromImage(gridImage);

  ResourceManager::loadTexture(10, &gridTex);
}

void loadCursorAnimation()
{
  ResourceManager::loadTextureFromFile(11, "assets/blue-grid-pointer.png");
  Animation *cursorAnimation = new Animation();
  cursorAnimation->setTexture(ResourceManager::getTexture(11));
  cursorAnimation->addFrame(new sf::IntRect(0, 0, 20, 20));
  cursorAnimation->addFrame(new sf::IntRect(20, 0, 20, 20));
  ResourceManager::loadAnimation(11, cursorAnimation);
}