#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include "scoreboard.h"
#include <vector>
#include <string>
#include <memory>

class Player;

class Controller {
    private:
        std::shared_ptr<Player> player1;
        std::shared_ptr<Player> player2;
        std::shared_ptr<Player> currentPlayer;
        std::shared_ptr<Board> board;
        bool gameEnded = false;
        std::vector<Move> MoveHistory;
        std::shared_ptr<ScoreBoard> scoreBoard;
        std::string promotedTo;
        bool gameStarted = false;
        Colour startTurnColour = Colour::White;
    public:
        Controller();
        ~Controller();
        void startGame(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
        void checkWin();
        void runGame( const Move &move);
        void endGame(bool resigned);
        void setScoreBoard(std::shared_ptr<ScoreBoard> sb);
        
        void setPromotedTo(std::string promotedType);
        
        void handleCommand(const std::string &command);

        std::shared_ptr<Square> stringToSquare(std::string squarestring);

        bool getGameEnded();
        void setGameEnded(bool ended);

        bool getGameStarted();
        void setGameStarted(bool started);

        void setStartTurnColour(Colour colour);
        Colour getStartTurnColour();

        void setupMode();
        std::shared_ptr<Player> getCurrentPlayer();

        void displayScore();
};

#endif