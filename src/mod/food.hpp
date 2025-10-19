#pragma once
#include "game.hpp"
#include "snakeBody.hpp"
class Food {
  int x, y;
  char data = '*';

public:
  Food();
  void genFood(Game &board, Snake &snake, bool &isEaten);
  void updateFood(Snake &snake, bool &isEaten);
  void resetFood(Game &board, Snake &snake, bool &isEaten);
};
