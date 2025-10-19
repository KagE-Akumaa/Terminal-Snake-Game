#pragma once

#include "game.hpp"
struct cord {

  int x, y;
};
struct SnakeBody {
  char data = 'o';
  cord pos;
  SnakeBody *next;
};
struct Direction {
  int dx, dy;
};

class Snake {
public:
  SnakeBody *head, *tail;
  Snake();
  void initSnake(Game &board);
  Direction SnakeDir;
  bool SnakeBodyCollision(int x, int y);
  void input();
  void updateSnake(Game &board, bool &game, bool &isEaten, int &score);
  void resetSnake(Game &board);
};
