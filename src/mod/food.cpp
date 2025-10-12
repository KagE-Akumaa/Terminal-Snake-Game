#include "food.hpp"
#include "snakeBody.hpp"
#include <random>
Food::Food() { data = '*'; }
std::random_device rx, ry;
std::mt19937 genx(rx());
std::mt19937 geny(ry());

void Food::genFood(Game &board, Snake &snake, bool &isEaten) {

  if (isEaten) {
    // gen random food update grid
    std::uniform_int_distribution<> distx(1, board.WIDTH - 2);
    std::uniform_int_distribution<> disty(1, board.HEIGHT - 2);

    do {
      x = distx(genx);
      y = disty(geny);
    } while (snake.SnakeBodyCollision(x, y));
    board.grid[y][x] = data;
    isEaten = false;
  }
}
void Food::updateFood(Snake &snake, bool &isEaten) {
  if (x == snake.head->pos.x && y == snake.head->pos.y) {
    isEaten = true;
    // increase the size of snake
    // basically insert at head for linked list
  }
}
