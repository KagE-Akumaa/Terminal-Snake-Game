#pragma once
#include <vector>
//
// init game
class Game {

public:
  int HEIGHT, WIDTH;
  Game(int HEIGHT, int WIDTH);
  void genGrid();
  void printGrid();
  void resetGrid();

  std::vector<std::vector<char>> grid;
  std::vector<std::vector<char>> getGrid();
  int getHeight();
  int getWidth();
};
