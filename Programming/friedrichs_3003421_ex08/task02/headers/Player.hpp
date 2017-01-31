#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Board.hpp"
#include "Coord.hpp"

class Player {
  public:
    virtual void play(Board &board);
    virtual Coord getInput(const Board &board);
    char getSymbol() const { return symbol; }

  protected:
    Player(const int playerNumber, const char symbol) : playerNumber(playerNumber), symbol(symbol) {}
    int playerNumber;
    char symbol;

  friend std::ostream &operator<<(std::ostream &os, Player &player);
};

std::ostream &operator<<(std::ostream &os, Player &player);

#endif
