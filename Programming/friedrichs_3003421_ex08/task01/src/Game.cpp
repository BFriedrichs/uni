#include <iostream>
#include "Game.hpp"
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"
#include "Board.hpp"

Game::Game(int gameType) {
  this->player1 = new HumanPlayer(1, 'X');

  switch(gameType) {
    case H_VS_H:
      this->player2 = new HumanPlayer(2, 'O');
      break;
    case H_VS_AI_MM:
      this->player2 = new AIPlayer(2, 'O', AIPlayer::RANDOM);
      break;
    case H_VS_AI_R:
      this->player2 = new AIPlayer(2, 'O', AIPlayer::RANDOM);
      break;
    default:
      this->player2 = new HumanPlayer(2, 'O');
      break;
  }

  this->board = new Board();
  this->board->setPlayingSymbols(this->player1->getSymbol(), this->player2->getSymbol());
}

Game::~Game() {
  delete this->board;
  delete this->player1;
  delete this->player2;
}

void Game::start() {
  std::cout << *this->board << std::endl;
  std::cout << *this->player1 << ": " << this->player1->getSymbol() << std::endl;
  std::cout << *this->player2 << ": " << this->player2->getSymbol() << std::endl;
  int currentPlayer = 1;
  while(!this->gameEnded) {
    turn(currentPlayer);
    std::cout << *this->board << std::endl;

    if(this->checkWinner(currentPlayer)) {
        std::cout << "=============" << std::endl;
        std::cout << "Player " << currentPlayer << " won!" << std::endl;
        std::cout << "=============" << std::endl << std::endl;
        this->gameEnded = true;
    } else {
        this->gameEnded = !this->board->hasAvailableMoves();
    }

    currentPlayer = (currentPlayer % 2) + 1;
  }
}

void Game::turn(const int playerNum) {
  switch(playerNum) {
    case 1:
      this->player1->play(*this->board);
      break;
    case 2:
      this->player2->play(*this->board);
      break;
    default:
      break;
  }
}

bool Game::checkWinner(const int currentPlayer) const {
  for(int j = 0; j < 3; j++) {
    if((this->board->getSpace(j, 0) == currentPlayer &&
        this->board->getSpace(j, 1) == currentPlayer &&
        this->board->getSpace(j, 2) == currentPlayer) ||

       (this->board->getSpace(0, j) == currentPlayer &&
        this->board->getSpace(1, j) == currentPlayer &&
        this->board->getSpace(2, j) == currentPlayer) ||

       (this->board->getSpace(0, 0) == currentPlayer &&
        this->board->getSpace(1, 1) == currentPlayer &&
        this->board->getSpace(2, 2) == currentPlayer) ||

       (this->board->getSpace(2, 0) == currentPlayer &&
        this->board->getSpace(1, 1) == currentPlayer &&
        this->board->getSpace(0, 2) == currentPlayer)) {

        return true;
    }
  }
  return false;
}
