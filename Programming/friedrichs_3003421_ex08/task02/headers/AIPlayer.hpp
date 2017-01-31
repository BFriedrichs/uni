#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.hpp"
#include "Board.hpp"
#include "Coord.hpp"

class AIPlayer : public Player {
  public:
    enum MODES {RANDOM, MINIMAX};
    AIPlayer(const int playerNumber, const char symbol, int mode) : Player(playerNumber, symbol), mode(mode) {}
    virtual Coord getInput(const Board &board);

  private:
    int mode;
    int calcTurn(const Board &board, const int currentPlayer, const bool isEntry = false);
};

#endif
