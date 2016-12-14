#include <iostream>
#include "Player.hpp"

void Player::play(Board &board) {
  std::cout << *this << "'s turn" << std::endl << std::endl;
  int rowInput;
  int colInput;

  do {
    rowInput = this->getInput("row");
    colInput = this->getInput("column");
  } while(!board.isFree(rowInput, colInput));

  board.insert(rowInput, colInput, this->playerNumber);
}

std::ostream &operator<<(std::ostream &os, Player &player) {
  os << "Player " << player.playerNumber;
  return os;
}

int Player::getInput(const char select[]) {
  std::cout << "You should never call this function on the base Player class!" << std::endl;
  return -1;
}
