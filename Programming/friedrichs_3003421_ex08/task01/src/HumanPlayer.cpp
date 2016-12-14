#include <iostream>
#include "HumanPlayer.hpp"

int HumanPlayer::getInput(const char select[]) {
  int val;

  std::cout << "Select a " << select << ": ";
  std::cin >> val;

  return --val;
}
