#include <iostream>
#include "Board.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
  public:
    virtual void play(Board &board);
    virtual int getInput(const char select[]);
    char getSymbol() const { return symbol; }

  protected:
    Player(const int playerNumber, const char symbol) : playerNumber(playerNumber), symbol(symbol) {}
    int playerNumber;
    char symbol;

  friend std::ostream &operator<<(std::ostream &os, Player &player);
};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
