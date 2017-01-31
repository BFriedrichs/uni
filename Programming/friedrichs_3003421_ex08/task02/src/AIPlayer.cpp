#include <random>
#include "AIPlayer.hpp"

/**
 * Virtual method that creates inputs dependent on the mode of the AI
 *
 * @param const Board board - Board in case it's require for the logic to make an input
 * @return Coord - Position for input
 */
Coord AIPlayer::getInput(const Board &board) {
  Coord result = {-1, -1};
  switch(this->mode) {
    case RANDOM:
      // could search for a free spot but we can also just repeat this until we hit one
      result.row = rand() % 3;
      result.col = rand() % 3;
      break;
    case MINIMAX:
      int index = calcTurn(board, this->playerNumber, true);
      result.row = index/3;
      result.col = index%3;
      break;
  }
  return result;
}

/**
 * @param const Board board - Board because it's require for the logic to make an input
 * @param const int currentPlayer - Which current are we calculating the turn for
 * @param const bool isEntry - default: false - Should only be true in the very first iteration
 * @return int - index (0-9) of coordinate when done OR
 *               current best result while in iteration (-1,0,1)
 */
int AIPlayer::calcTurn(const Board &board, const int currentPlayer, const bool isEntry) {
  const bool winSelf = board.checkWinner(this->playerNumber);
  const bool winOther = board.checkWinner(this->playerNumber % 2 + 1);
  const bool max = this->playerNumber == currentPlayer; // are we checking for max or min?

  // if noone has won AND there are free spaces we have to continue
  if(!(winSelf || winOther) && board.hasAvailableMoves()) {
    int bestResult;
    int bestResultIndex;
    bool resFound = false;

    for(int i = 0; i < 9; i++) {
      Coord coord = {i/3, i%3};

      if(board.isFree(coord, false)) {
        // Clone board and calc the next turn for it
        Board temp = board;
        temp.insert(coord, currentPlayer);
        int result = calcTurn(temp, currentPlayer % 2 + 1);

        // First result or maximin algorithm, save best result and its index
        if(!resFound || (max && result > bestResult) || (!max && result < bestResult)) {
          resFound = true;
          bestResult = result;
          bestResultIndex = i;  // we only really need that for the very end
        }
      }
    }
    if(isEntry) {
      return bestResultIndex; // when we are done return the index
    }

    return bestResult;  // otherwise return the saved best result
  }

  if(winSelf) {
    return 1; // return 1 if i won
  }

  if(winOther) {
    return -1; // -1 if enemy won
  }

  return 0; // board is full - no winner
}
