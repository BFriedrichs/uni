#include <iostream>
#include "Player.hpp"

/**
 * Play method is the same for each player
 * First it prints a message whose turn it is
 * Then it waits for an input until a correct one is made and inputs it into the board
 *
 * @param Board board - Board to make your input
 */
void Player::play(Board &board) {
  std::cout << *this << "'s turn" << std::endl << std::endl;
  Coord input = {-1, -1};
  do {
    input = this->getInput(board);
  } while(!board.isFree(input));

  board.insert(input, this->playerNumber);
}

/**
 * Print player number
 *
 * @param std::ostream os - Output stream
 * @param const Player player - Player to print
 * @return std::ostream - Output stream
 */
std::ostream &operator<<(std::ostream &os, Player &player) {
  os << "Player " << player.playerNumber;
  return os;
}

/**
 * Virtual method that should never be called on the base object
 *
 * @param Board board - Board in case it's require for the logic to make an input
 * @return Coord - Position for input
 */
Coord Player::getInput(const Board &board) {
  std::cout << "You should never call this function on the base Player class!" << std::endl;
  return Coord{-1, -1};
}
