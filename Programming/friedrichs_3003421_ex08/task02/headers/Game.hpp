#ifndef GAME_H
#define GAME_H

#include "Player.hpp"
#include "Board.hpp"

class Game {
  public:
    enum GAME_TYPES {H_VS_H, H_VS_AI_MM, H_VS_AI_R};
    Game(const int gameType);
    ~Game();
    void start();

  private:
    bool gameEnded = false;
    Player *player1;
    Player *player2;
    Board *board;
    void turn(const int playerNum);
};

#endif
