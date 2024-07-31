#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "board.h"
#include "scoreboard.h"
#include <vector>
#include <string>

class Player;

// Controller class, responsible for handling the game logic
class Controller {
    private:
        Player* player1;
        Player* player2;
        //current player pointer that will point to the 2 above
        Player* currentPlayer;
        Board* board;
        //game state flags
        bool gameStarted = false;
        bool gameEnded = false;
        Colour startTurnColour = Colour::White;
        ScoreBoard* scoreBoard;
        //string to store the type of piece a pawn is promoted to
        std::string promotedTo;
    public:
        //constructor and destructor
        Controller(Player* player1, Player* player2);
        ~Controller();
        //starting a game once "game" command is entered
        void startGame(Player &p1, Player &p2);
        //check if any king is in checkmate
        void checkWin();
        //once a move in given, play it on the board
        void runGame( const Move &move);
        //game end logic, either a resign or checkmate
        void endGame(bool resigned);
        //parse input from the user and behave accordingly
        void handleCommand(const std::string &command);
        void setScoreBoard(ScoreBoard* sb);
        //display the current score
        void displayScore();
        //setup custom board logic
        void setupMode();
        //return associated square based off of string input
        Square* stringToSquare(std::string squarestring);
        
        //getters and setters
        void setPromotedTo(std::string promotedType);

        bool getGameEnded();

        bool getGameStarted();

        void setStartTurnColour(Colour colour);
        Colour getStartTurnColour();

        Player* getCurrentPlayer();

        void displayScore();

        void printLatestMove(const std::vector<Move>& MoveHistory);

        std::string coordinateToChessNotation(int x, int y);
};

#endif