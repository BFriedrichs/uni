#include <iostream>
#include "Game.hpp"

void showMenu() {
  std::cout << "Choose your game mode." << std::endl;
  std::cout << "(1) Human vs. Human" << std::endl;
  std::cout << "(2) Human vs. Compute (Minimax)" << std::endl;
  std::cout << "(3) Human vs. Human (Random)" << std::endl;
  std::cout << "(4) Exit Program" << std::endl;
}

bool exitProgram = false;
char input;

int main(int argc, char *argv[]) {
  while(!exitProgram) {
    showMenu();
    std::cin >> input;
    Game *currentGame;
    switch(input) {
      case '1':
        currentGame = new Game(Game::H_VS_H);
        break;
      case '2':
        currentGame = new Game(Game::H_VS_AI_MM);
        break;
      case '3':
        currentGame = new Game(Game::H_VS_AI_R);
        break;
      case '4':
        exitProgram = true;
        break;
      default:
        break;
    }

    if(currentGame != NULL) {
      currentGame->start();
      delete currentGame;
      currentGame = NULL;
    }

  }
  return 0;
};
