#include "food.hpp"
#include "game.hpp"
#include "snakeBody.hpp"
#include "terminal.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

void gentext(string &restartGame, Game &board) {
  int n = board.getHeight();
  int m = board.getWidth();
  int strSize = restartGame.size();

  int k = 0;
  for (int i = n / 2; i < n - 1; i++) {
    for (int j = m / 8; j < m - 1; j++) {
      if (k == restartGame.size())
        break;
      board.grid[i][j] = restartGame[k++];
    }
  }
}
int main() {
  int HEIGHT = 20, WIDTH = 50;
  Game board(HEIGHT, WIDTH);
  Snake snake;

  string test(WIDTH / 2 - 5, ' '), space((WIDTH - 14 - WIDTH / 2) - 3, ' ');
  Food food;
  Terminal term;
  term.initTerminal();
  snake.initSnake(board);
  int score = 0, highScore = 0;
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
      // need to chech the next char if the char is r then restart the game else
      // quit the game

      system("clear");
      string restartGame = "Press R for restart and Q for quit";
      // just for fun

      // cout << restartGame << endl;
      gentext(restartGame, board);

      board.printGrid();

      char ch;
      int n = -1;

      while (true) {
        int n = read(STDIN_FILENO, &ch, 1);
        if (n > 0) {
          ch = tolower(ch);
          if (ch == 'r' || ch == 'q')
            break;
        }
      }
      if (ch == 'r') {
        gameRunning = true;
        if (score > highScore) {
          highScore = score;
        }
        score = 0;
        snake.resetSnake(board);
        board.resetGrid();
        food.resetFood(board, snake, isEaten);
        continue;

      } else {
        score = highScore;
        break;
      }
    }
    // grid update
    // draw

    board.printGrid();
    cout << test << "Score " << score << " " << space << "High Score "
         << highScore << endl;
    usleep(150000); // the value is in microseconds
  }
  term.restoreTerminal();
  cout << "Game over" << " " << "Score " << highScore << endl;
}
