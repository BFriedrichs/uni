#include <iostream>
#include <random>
#include "AIPlayer.hpp"

int AIPlayer::getInput(const char select[]) {
  return rand() % 3;
}
