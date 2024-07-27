#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include "scoreboard.h"
#include <vector>
#include <string>
class Controller {
    private:
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        Board board;
        bool gameEnded;
        std::vector<Move> MoveHistory;
        ScoreBoard* scoreBoard;
        std::string promotedTo;
    public:
        Controller(Player* player1, Player* player2);
        void startGame(Player &p1, Player &p2);
        void checkWin();
        void runGame(Player &p1, Player &p2);
        void endGame(bool resigned);
        void Controller::playTurn(Player* p);
        void setScoreBoard(ScoreBoard* sb);
        PieceType getPromotedTo();
        void setPromotedTo(std::string promotedType, Colour colour);
        void handleCommand(const std::string command);
};

#endif