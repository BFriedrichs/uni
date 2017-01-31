#ifndef HPLAYER_H
#define HPLAYER_H

#include "Player.hpp"
#include "Board.hpp"
#include "Coord.hpp"

class HumanPlayer : public Player {
  public:
    HumanPlayer(const int playerNumber, const char symbol) : Player(playerNumber, symbol) {}
    virtual Coord getInput(const Board &board);
};

#endif
