#include "Player.hpp"

#ifndef AIPLAYER_H
#define AIPLAYER_H

class AIPlayer : public Player {
  public:
    enum MODES {RANDOM, MINIMAX};
    AIPlayer(const int playerNumber, const char symbol, int mode) : Player(playerNumber, symbol), mode(mode) {}
    virtual int getInput(const char select[]);

  private:
    int mode;
};

#endif
