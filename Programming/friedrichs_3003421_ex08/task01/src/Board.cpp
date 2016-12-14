#include "Board.hpp"

Board::Board() {
  this->setPlayingSymbols();
  this->board = new int*[3]();

  for(int i = 0; i < 3; i++) {
    this->board[i] = new int[3]();
  }
}

Board::~Board() {
  for(int i = 0; i < 3; i++) {
    delete[] this->board[i];
  }

  delete[] this->board;
}

void Board::insert(const int row, const int col, const int value) {
  if(row < 0 || row > 2 || col < 0 || col > 2) {
    std::cout << "Invalid field selection" << std::endl;
  } else {
    this->board[row][col] = value;
  }
}

void Board::setPlayingSymbols(const char player1, const char player2) {
    this->mapSymbol[0] = ' ';
    this->mapSymbol[1] = player1;
    this->mapSymbol[2] = player2;
}

bool Board::isFree(const int row, const int col) const {
  bool isFree = this->board[row][col] == 0;
  if(row < 0 || row > 2 || col < 0 || col > 2 || !isFree) {
    std::cout << "Invalid field selection" << std::endl;
    return false;
  }
  return true;
}

bool Board::hasAvailableMoves() const {
  int freeSpaces = 0;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      freeSpaces += this->board[i][j] == 0;
    }
  }
  return freeSpaces != 0;
}

int Board::getSpace(const int row, const int col) const {
  if(row < 0 || row > 2 || col < 0 || col > 2) {
    return -1;
  }
  return this->board[row][col];
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
  os << "    1   2   3  " << std::endl;
  for(int i = 0; i < 3; i++) {
    os << "  -------------" << std::endl;
    os << i+1 << " | " << board.mapSymbol[board.board[i][0]];
    os << " | " << board.mapSymbol[board.board[i][1]];
    os << " | " << board.mapSymbol[board.board[i][2]];
    os << " | " << std::endl;
  }
  os << "  -------------" << std::endl;

  return os;
}
