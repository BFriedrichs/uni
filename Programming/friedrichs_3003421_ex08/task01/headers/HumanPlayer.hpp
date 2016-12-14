#include <iostream>
#include "Player.hpp"

#ifndef HPLAYER_H
#define HPLAYER_H

class HumanPlayer : public Player {
  public:
    HumanPlayer(const int playerNumber, const char symbol) : Player(playerNumber, symbol) {}
    virtual int getInput(const char select[]);
};

#endif
