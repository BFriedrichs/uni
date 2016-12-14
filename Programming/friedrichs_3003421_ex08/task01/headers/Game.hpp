#include <iostream>
#include "Player.hpp"
#include "Board.hpp"

#ifndef GAME_H
#define GAME_H

class Game {
  public:
    enum GAME_TYPES {H_VS_H, H_VS_AI_MM, H_VS_AI_R};
    Game(int gameType);
    ~Game();
    void start();

  private:
    bool gameEnded = false;
    Player *player1;
    Player *player2;
    Board *board;
    void turn(const int playerNum);
    bool checkWinner(const int currentPlayer) const;

};

#endif
