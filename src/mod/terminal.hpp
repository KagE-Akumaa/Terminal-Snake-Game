#pragma once
#include <termios.h>

class Terminal {
  termios oldt;

public:
  Terminal();
  void initTerminal();
  void restoreTerminal();
};
