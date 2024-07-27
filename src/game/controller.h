#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include <vector>
class Controller {
    private:
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        Board board;
        bool gameEnded;
        std::vector<Move> MoveHistory;
    public:
        Controller(Player* player1, Player* player2);
        void startGame(Player &p1, Player &p2);
        void checkWin();
        void runGame(Player &p1, Player &p2);
        void endGame(bool resigned);
        void Controller::playTurn(Player* p);
};

#endif