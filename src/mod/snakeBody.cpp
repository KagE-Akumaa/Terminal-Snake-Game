#include "snakeBody.hpp"
#include <unistd.h>
Snake::Snake() {
  head = nullptr;
  tail = nullptr;
  SnakeDir = {1, 0};
}

void Snake::initSnake(Game &board) {
  // Make a node for snake at centre
  head = new SnakeBody;

  head->pos.x = board.WIDTH / 2;
  head->pos.y = board.HEIGHT / 2;
  head->next = nullptr;
  tail = head;

  // update the grid so snake appear on centre of grid
  board.grid[head->pos.y][head->pos.x] = head->data;
}
bool Snake::SnakeBodyCollision(int x, int y) {
  SnakeBody *temp = head;
  while (temp) {
    if (temp->pos.x == x && temp->pos.y == y) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
void Snake::updateSnake(Game &board, bool &game, bool &isEaten, int &score) {
  int newX = head->pos.x + SnakeDir.dx;
  int newY = head->pos.y + SnakeDir.dy;

  if (newX <= 0 || newX >= board.WIDTH - 1 || newY <= 0 ||
      newY >= board.HEIGHT - 1) {

    game = false;
    return;
  }

  if (SnakeBodyCollision(newX, newY)) {
    game = false;
    return;
  }
  if (isEaten) {
    SnakeBody *n = new SnakeBody;
    n->pos.x = newX;
    n->pos.y = newY;
    // upade the head
    n->next = head;
    head = n;
    // UPdate the score too;
    score++;
  }
  if (head == tail) {
    board.grid[head->pos.y][head->pos.x] = ' ';
    head->pos.x += SnakeDir.dx;
    head->pos.y += SnakeDir.dy;

    board.grid[head->pos.y][head->pos.x] = head->data;
    return;
  }

  // update the head to the new head
  SnakeBody *newBody = new SnakeBody;
  newBody->pos.x = newX;
  newBody->pos.y = newY;

  newBody->next = head;
  head = newBody;

  // Clear the grid
  board.grid[tail->pos.y][tail->pos.x] = ' ';
  // Remove the tail

  SnakeBody *temp = tail;
  SnakeBody *prev = head;

  while (prev->next != tail) {
    prev = prev->next;
  }
  prev->next = nullptr;
  tail = prev;
  delete (temp);
  // update the new head
  board.grid[head->pos.y][head->pos.x] = head->data;
}
char p = ' ';
char peq = ' ';
void Snake::input() {
  char ch;
  int n = read(STDIN_FILENO, &ch, 1);
  // if no input is given n = -1 no need to do anything
  if (n > 0) {
    // need to check the character and then update the snakeDir accordingly

    if ((p == 'w' && ch == 's') || (p == 's' && ch == 'w'))
      return;
    else if ((p == 'a' && ch == 'd') || (p == 'd' && ch == 'a'))
      return;

    p = ch;
    if (ch == '\x1b') {
      char seq[2];
      read(STDIN_FILENO, &seq[0], 1);
      read(STDIN_FILENO, &seq[1], 1);

      if (seq[0] == '[') {

        if ((peq == 'A' && seq[1] == 'B') || (peq == 'B' && seq[1] == 'A')) {
          return;
        } else if ((peq == 'C' && seq[1] == 'D') ||
                   (peq == 'D' && seq[1] == 'C'))
          return;
        switch (seq[1]) {
        case 'A':

          SnakeDir.dx = 0;
          SnakeDir.dy = -1;
          break;
        case 'B':
          SnakeDir.dx = 0;
          SnakeDir.dy = 1;
          break;
        case 'C':
          SnakeDir.dx = 1;
          SnakeDir.dy = 0;
          break;
        case 'D':
          SnakeDir.dx = -1;
          SnakeDir.dy = 0;
          break;
        }
      }

      peq = seq[1];
      return;
    }
    switch (ch) {
    case 'w':
      SnakeDir.dx = 0;
      SnakeDir.dy = -1;
      break;
    case 's':
      SnakeDir.dx = 0;
      SnakeDir.dy = 1;
      break;
    case 'a':
      SnakeDir.dx = -1;
      SnakeDir.dy = 0;
      break;
    case 'd':
      SnakeDir.dx = 1;
      SnakeDir.dy = 0;
      break;
    }
  }
}
void Snake::resetSnake(Game &board) {

  head->pos.x = board.WIDTH / 2;
  head->pos.y = board.HEIGHT / 2;
  head->next = nullptr;
  tail = head;

  // update the grid so snake appear on centre of grid
  board.grid[head->pos.y][head->pos.x] = head->data;
}
