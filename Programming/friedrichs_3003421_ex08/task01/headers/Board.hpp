#include <iostream>

#ifndef BOARD_H
#define BOARD_H

class Board {
  public:
    Board();
    ~Board();
    void insert(const int row, const int col, const int val);
    void setPlayingSymbols(const char player1 = '1', const char player2 = '2');
    bool isFree(const int row, const int col) const;
    bool hasAvailableMoves() const;
    int getSpace(const int row, const int col) const;
    
  private:
    int **board;
    char mapSymbol[3];

  friend std::ostream& operator<<(std::ostream &os, const Board &obj);
};

std::ostream& operator<<(std::ostream &os, const Board &obj);

#endif
