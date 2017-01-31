#include "Board.hpp"

/**
 * Normal Constructor
 */
Board::Board() {
  this->setPlayingSymbols();
  this->board = new int*[3]();

  for(int i = 0; i < 3; i++) {
    this->board[i] = new int[3]();
  }
}

/**
 * Copy constructor
 *
 * @param const Board &obj - board to copy
 */
Board::Board(const Board &obj) {
  this->board = new int*[3]();
  memcpy(this->mapSymbol, obj.mapSymbol, sizeof(char) * 3);

  for(int i = 0; i < 3; i++) {
    this->board[i] = new int[3]();
    memcpy(this->board[i], obj.board[i], sizeof(int) * 3);
  }
}

/**
 * Normal destructor
 */
Board::~Board() {
  for(int i = 0; i < 3; i++) {
    delete[] this->board[i];
  }

  delete[] this->board;
}

/**
 * Inserts a value at the desired location
 * Prints error message on coord out of bounds
 *
 * @param const Coord coord - coordinate to insert at
 * @param const int value - value to insert at coord
 */
void Board::insert(const Coord &coord, const int value) {
  if(coord.row < 0 || coord.row > 2 || coord.col < 0 || coord.col > 2) {
    std::cout << "Invalid field selection" << std::endl;
  } else {
    this->board[coord.row][coord.col] = value;
  }
}

/**
 * Sets the chars that will be displayed
 *
 * @param const char player1 - default: '1' - Char for player 1
 * @param const char player2 - default: '2' - Char for player 2
 */
void Board::setPlayingSymbols(const char player1, const char player2) {
    this->mapSymbol[0] = ' ';
    this->mapSymbol[1] = player1;
    this->mapSymbol[2] = player2;
}

/**
 * Returns true if the coordinate is still free
 * Verbose control text output if it isnt.
 *
 * @param const Coord coord - Coordinate to be checked
 * @param const bool verbose - default: true - Controls text output
 *
 * @return bool - Coordinate is free?
 */
bool Board::isFree(const Coord &coord, const bool verbose) const {
  bool isFree = this->board[coord.row][coord.col] == 0;
  if(coord.row < 0 || coord.row > 2 || coord.col < 0 || coord.col > 2 || !isFree) {
    if(verbose) {
      std::cout << "Invalid field selection" << std::endl;
    }
    return false;
  }
  return true;
}

/**
 * Returns true if there is still free spaces left
 *
 * @result bool - Board has free spaces?
 */
bool Board::hasAvailableMoves() const {
  int freeSpaces = 0;
  for(int i = 0; i < 9; i++) {
    freeSpaces += this->board[i/3][i%3] == 0;
  }
  return freeSpaces != 0;
}

/**
 * Returns true if the player supplied by argument won the game
 *
 * @param const int currentPlayer - Number of player to check win for
 * @result bool - Did player win?
 */
bool Board::checkWinner(const int currentPlayer) const {
  for(int j = 0; j < 3; j++) {
    if((this->board[j][0] == currentPlayer &&
        this->board[j][1] == currentPlayer &&
        this->board[j][2] == currentPlayer) ||

       (this->board[0][j] == currentPlayer &&
        this->board[1][j] == currentPlayer &&
        this->board[2][j] == currentPlayer) ||

       (this->board[0][0] == currentPlayer &&
        this->board[1][1] == currentPlayer &&
        this->board[2][2] == currentPlayer) ||

       (this->board[2][0] == currentPlayer &&
        this->board[1][1] == currentPlayer &&
        this->board[0][2] == currentPlayer)) {

        return true;
    }
  }
  return false;
}

/**
 * Pretty print board
 *
 * @param std::ostream os - Output stream
 * @param const Board board - Board to print
 * @return std::ostream - Output stream
 */
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
