#include "game.hpp"
#include <iostream>

Game::Game(int HEIGHT, int WIDTH) {
  this->HEIGHT = HEIGHT;
  this->WIDTH = WIDTH;
  grid.assign(HEIGHT, std::vector<char>(WIDTH, ' '));
}
void Game::genGrid() {

  int top = 0, left = 0, right = WIDTH - 1, bottom = HEIGHT - 1;
  int n = HEIGHT;
  int m = WIDTH;
  for (int row = 0; row < n; row++) {
    grid[row][left] = '#';
    grid[row][right] = '#';
  }

  for (int col = 0; col < m; col++) {
    grid[top][col] = '#';
    grid[bottom][col] = '#';
  }
}

void Game::printGrid() {
  int n = HEIGHT;
  int m = WIDTH;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << grid[i][j];
    }

    std::cout << std::endl;
  }
}
std::vector<std::vector<char>> Game::getGrid() { return grid; }
int Game::getHeight() { return HEIGHT; }
int Game::getWidth() { return WIDTH; }
void Game::resetGrid() {
  int n = HEIGHT;
  int m = WIDTH;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] != '#') {
        grid[i][j] = ' ';
      }
    }
  }
}
