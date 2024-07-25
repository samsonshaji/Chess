#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
class Controller {
    private:
        Player* player1;
        Player* player2;
        Board board;
        bool gameEnded;
    public:
        Controller(Player* player1, Player* player2);
        void startGame(Player &p1, Player &p2);
        void checkWin();
        void runGame();
        void endGame(bool resigned);
};

#endif