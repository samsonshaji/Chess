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
        bool gameEnded = false;
        std::vector<Move> MoveHistory;
        ScoreBoard* scoreBoard;
        std::string promotedTo;
        bool gameStarted = false;
        Colour startTurnColour = Colour::White;
    public:
        Controller(Player* player1, Player* player2);
        void startGame(Player &p1, Player &p2);
        void checkWin();
        void runGame( const Move &move);
        void endGame(bool resigned);
        void setScoreBoard(ScoreBoard* sb);
        
        void setPromotedTo(std::string promotedType);
        
        void handleCommand(const std::string &command);

        Square* stringToSquare(std::string squarestring);

        bool getGameEnded();
        void setGameEnded(bool ended);

        bool getGameStarted();
        void setGameStarted(bool started);

        void setStartTurnColour(Colour colour);
        Colour getStartTurnColour();

        void setupMode();
        Player* getCurrentPlayer();

        void displayScore();
};

#endif