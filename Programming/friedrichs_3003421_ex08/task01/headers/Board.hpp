#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Coord.hpp"

class Board {
  public:
    Board();
    Board(const Board &obj);
    ~Board();
    void insert(const Coord &coord, const int val);
    void setPlayingSymbols(const char player1 = '1', const char player2 = '2');
    bool isFree(const Coord &coord, const bool verbose = true) const;
    bool hasAvailableMoves() const;
    bool checkWinner(const int currentPlayer) const;

  private:
    int **board;
    char mapSymbol[3];

  friend std::ostream& operator<<(std::ostream &os, const Board &obj);
};

std::ostream& operator<<(std::ostream &os, const Board &obj);

#endif
