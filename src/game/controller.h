#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include "scoreboard.h"
#include <vector>
#include <string>

class Player;

class Controller {
    private:
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        Board* board;
        bool gameStarted = false;
        ScoreBoard* scoreBoard;
        bool setUp = false;
    public:
        Controller(Player* player1, Player* player2);
        void startGame(Player &p1, Player &p2);
        void checkWin();
        void playTurn(const Move &move);
        void endGame(bool resigned);
        void setScoreBoard(ScoreBoard* sb);
        
        void handleCommand(const std::string &command);

        bool getGameStarted();
        void setGameStarted(bool started);

        Player* getCurrentPlayer() const;

        void setupMode();
};

#endif