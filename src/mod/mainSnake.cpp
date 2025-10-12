#include "food.hpp"
#include "game.hpp"
#include "snakeBody.hpp"
#include "terminal.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
  int HEIGHT = 20, WIDTH = 50;
  Game board(HEIGHT, WIDTH);
  Snake snake;

  string test(WIDTH / 2 - 5, ' ');
  Food food;
  Terminal term;
  term.initTerminal();
  snake.initSnake(board);
  int score = 0;
  bool gameRunning = true, isEaten = true;
  cout << "\033[2J";
  while (gameRunning) {

    // system("clear");
    cout << "\033[H";

    // Initialize
    board.genGrid();
    food.genFood(board, snake, isEaten);
    // update
    snake.input();
    food.updateFood(snake, isEaten);

    snake.updateSnake(board, gameRunning, isEaten, score);
    if (!gameRunning) {
      break;
    }
    // grid update
    // draw

    board.printGrid();
    cout << test << "Score " << score << endl;
    usleep(150000); // the value is in microseconds
  }
  term.restoreTerminal();
  cout << "Game over" << " " << "Score " << score << endl;
}
