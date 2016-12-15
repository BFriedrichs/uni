#include <iostream>
#include "HumanPlayer.hpp"

/**
 * Virtual method that waits for 2 inputs of a human player
 *
 * @param Board board - Board in case it's require for the logic to make an input
 * @return Coord - Position for input
 */
Coord HumanPlayer::getInput(const Board &board) {
  Coord result = {-1, -1};

  std::cout << "Select a row: ";
  std::cin >> result.row;

  std::cout << "Select a column: ";
  std::cin >> result.col;

  // since the rows and cols are numbered 1,2,3 we decrease them by one
  result.row--;
  result.col--;

  return result;
}
