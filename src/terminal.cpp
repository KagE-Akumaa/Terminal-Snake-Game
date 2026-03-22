#include "terminal.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
Terminal::Terminal() { tcgetattr(STDIN_FILENO, &oldt); }

void Terminal::initTerminal() {

  termios newt;
  int olf;

  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  olf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, olf | O_NONBLOCK);
}

void Terminal::restoreTerminal() {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  system("clear");
}
