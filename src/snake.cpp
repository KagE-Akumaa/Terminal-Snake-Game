#include <fcntl.h>
#include <iostream>
#include <random>
#include <termios.h>
#include <unistd.h>
#include <vector>
using namespace std;

const int HEIGHT = 20, WIDTH = 50;
vector<vector<char>> grid(HEIGHT, vector<char>(WIDTH, ' '));

struct cord {

  int x, y;
};
struct SnakeBody {
  char data = 'o';
  cord pos;
  SnakeBody *next;
};
SnakeBody *head = nullptr;
SnakeBody *tail = nullptr;
struct Direction {
  int dx, dy;
};
Direction SnakeDir = {1, 0};
struct Food {
  int x, y;
  char data = '*';
};
//------------------------------------------------------//
// Stuct--------------------------------------/

void genGrid() {

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
void printGrid() {
  int n = HEIGHT;
  int m = WIDTH;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}
void initSnake(SnakeBody *&head) {
  // Make a node for snake at centre
  head = new SnakeBody;

  head->pos.x = WIDTH / 2;
  head->pos.y = HEIGHT / 2;
  head->next = nullptr;
  tail = head;

  // update the grid so snake appear on centre of grid
  grid[head->pos.y][head->pos.x] = head->data;
}
bool snakeBodyCollision(int x, int y, SnakeBody *&head) {
  SnakeBody *temp = head;
  while (temp) {
    if (temp->pos.x == x && temp->pos.y == y) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
void updateSnake(SnakeBody *&head, bool &game, bool &isEaten, int &score) {

  int newX = head->pos.x + SnakeDir.dx;
  int newY = head->pos.y + SnakeDir.dy;

  if (newX <= 0 || newX >= WIDTH - 1 || newY <= 0 || newY >= HEIGHT - 1) {

    cout << "Snake hit a wall" << endl;
    game = false;
    return;
  }

  if (snakeBodyCollision(newX, newY, head)) {
    cout << "Snake hit it's own body" << endl;
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
    grid[head->pos.y][head->pos.x] = ' ';
    head->pos.x += SnakeDir.dx;
    head->pos.y += SnakeDir.dy;

    grid[head->pos.y][head->pos.x] = head->data;
    return;
  }

  // update the head to the new head
  SnakeBody *newBody = new SnakeBody;
  newBody->pos.x = newX;
  newBody->pos.y = newY;

  newBody->next = head;
  head = newBody;

  // Clear the grid
  grid[tail->pos.y][tail->pos.x] = ' ';
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
  grid[head->pos.y][head->pos.x] = head->data;
}

// TODO: valid bound checks for snake body check, addition  of nodes, food
// generation Initialize terminal for raw mode
void initTerminal(termios &oldt) {

  termios newt;
  int olf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  olf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, olf | O_NONBLOCK);
}

void restoreTerminal(termios &oldt) {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  system("clear");
}
char p = ' ';
void getInput() {

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
random_device rx, ry;
mt19937 genx(rx());
mt19937 geny(ry());

void genFood(Food &food, bool &isEaten) {

  if (isEaten) {
    // gen random food update grid
    uniform_int_distribution<> distx(1, WIDTH - 2);
    uniform_int_distribution<> disty(1, HEIGHT - 2);

    do {
      food.x = distx(genx);
      food.y = disty(geny);
    } while (snakeBodyCollision(food.x, food.y, head));
    grid[food.y][food.x] = food.data;
    isEaten = false;
  }
}
void updateFood(Food &food, SnakeBody *&snake, bool &isEaten) {

  if (food.x == snake->pos.x && food.y == snake->pos.y) {
    isEaten = true;
    // increase the size of snake
    // basically insert at head for linked list
  }
}

int main() {

  genGrid();

  termios oldt;
  initTerminal(oldt);
  initSnake(head);

  int score = 0;
  bool game = true, isEaten = true;
  Food food;
  while (game) {
    // Need to clear the terminal use system("clear")
    system("clear");
    // take input
    //
    genFood(food, isEaten);
    getInput();
    updateFood(food, head, isEaten);
    updateSnake(head, game, isEaten, score);
    if (!game) {
      break;
    }
    // grid update
    printGrid();
    cout << "                   Score " << score << endl;
    usleep(150000); // the value is in microseconds
  }

  // Restore terminal and other settings
  restoreTerminal(oldt);
  cout << "Game over" << " " << "Score " << score << endl;
}
