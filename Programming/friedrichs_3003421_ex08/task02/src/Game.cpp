#include <iostream>
#include "Game.hpp"
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"


/**
 * Normal Constructor
 * Creates a new game dependent on supplied gameType
 *
 * @param const int gameType - What kind of game is played?
 */
Game::Game(const int gameType) {
  // Player 1 is always human
  this->player1 = new HumanPlayer(1, 'X');

  switch(gameType) {
    case H_VS_H:
      this->player2 = new HumanPlayer(2, 'O');
      break;
    case H_VS_AI_MM:
      this->player2 = new AIPlayer(2, 'O', AIPlayer::MINIMAX);
      break;
    case H_VS_AI_R:
      this->player2 = new AIPlayer(2, 'O', AIPlayer::RANDOM);
      break;
    default:
      this->player2 = new HumanPlayer(2, 'O');  // fallback
      break;
  }

  this->board = new Board();
  this->board->setPlayingSymbols(this->player1->getSymbol(), this->player2->getSymbol());
}

/**
 * Normal Destructor
 */
Game::~Game() {
  delete this->board;
  delete this->player1;
  delete this->player2;
}

/**
 * Once the game is created it can be started using this method.
 * It first prints the symbols for each player and then loops turns until either
 * one player wins or the board is full.
 * Prints win message before leaving loop if there is a winner.
 */
void Game::start() {
  std::cout << *this->board << std::endl;
  std::cout << *this->player1 << ": " << this->player1->getSymbol() << std::endl;
  std::cout << *this->player2 << ": " << this->player2->getSymbol() << std::endl;
  int currentPlayer = 1;
  while(!this->gameEnded) {
    this->turn(currentPlayer);

    if(this->board->checkWinner(currentPlayer)) {
        std::cout << "=============" << std::endl;
        std::cout << "Player " << currentPlayer << " won!" << std::endl;
        std::cout << "=============" << std::endl << std::endl;
        this->gameEnded = true;
    } else {
        this->gameEnded = !this->board->hasAvailableMoves();
    }

    // alternate players: 1 -> 2, 2 -> 1
    currentPlayer = currentPlayer % 2 + 1;
  }
}

/**
 * Decides which players turn it is and executes it
 * Then prints the current board state
 *
 * @param const int currentPlayer - Number of current Player
 */
void Game::turn(const int playerNum) {
  switch(playerNum) {
    case 1:
      this->player1->play(*this->board);
      break;
    case 2:
      this->player2->play(*this->board);
      break;
  }
  std::cout << *this->board << std::endl;
}
