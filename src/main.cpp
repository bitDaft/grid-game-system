#include <iostream>

#include "grid.h"

int main(int argc, char const *argv[])
{
  std::cout << "it builds";
  Grid *game = new Grid();
  game->run(); 
  return 0;
}
