#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include "scoreboard.h"
#include <vector>
#include <string>
#include <memory>

class Player;

// Controller class, responsible for handling the game logic
class Controller {
    private:
        std::shared_ptr<Player> player1;
        std::shared_ptr<Player> player2;
        std::shared_ptr<Player> currentPlayer;
        std::shared_ptr<Board> board;
        bool gameEnded = false;
        bool gameStarted = false;
        Colour startTurnColour = Colour::White;
        std::shared_ptr<ScoreBoard> scoreBoard;
        //string to store the type of piece a pawn is promoted to
        std::string promotedTo;
    public:
        //constructor and destructor
        Controller();
        ~Controller();
        void startGame(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
        void checkWin();
        //once a move in given, play it on the board
        void runGame( const Move &move);
        //game end logic, either a resign or checkmate
        void endGame(bool resigned);
        //parse input from the user and behave accordingly
        void handleCommand(const std::string &command);
        void setScoreBoard(std::shared_ptr<ScoreBoard> sb);
        //display the current score
        void displayScore();
        //setup custom board logic
        void setupMode();
        //return associated square based off of string input
        std::shared_ptr<Square> stringToSquare(std::string squarestring);
        
        //getters and setters
        void setPromotedTo(std::string promotedType);

        bool getGameEnded();

        bool getGameStarted();

        void setStartTurnColour(Colour colour);
        Colour getStartTurnColour();

        std::shared_ptr<Player> getCurrentPlayer();
        void printLatestMove(const std::vector<Move>& MoveHistory);
        std::string coordinateToChessNotation(int x, int y);
};

#endif