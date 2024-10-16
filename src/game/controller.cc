#include <iostream>
#include <sstream>

#include "bishop.h"
#include "board.h"
#include "controller.h"
#include "graphicsobserver.h"
#include "human.h"
#include "king.h"
#include "knight.h"
#include "move.h"
#include "pawn.h"
#include "queen.h"
#include "robot.h"
#include "robotLevelFour.h"
#include "robotLevelOne.h"
#include "robotLevelThree.h"
#include "robotLevelTwo.h"
#include "rook.h"
#include "scoreboard.h"
#include "square.h"
#include "textobserver.h"

Controller::Controller(Player *player1, Player *player2) : player1(player1), player2(player2), currentPlayer(player1), gameEnded(false) {
    // create a new board, scoreBoard and set the controller
    board = new Board();
    board->setController(this);
    scoreBoard = new ScoreBoard();
    new TextObserver(*board);
    new GraphicsObserver(*board);
}

Controller::~Controller() {
    //delete all pieces off the board
    for (auto move : board->getMoveStack()) {
        if (move.getCapturedPiece() != nullptr) {
            delete move.getCapturedPiece();
            move.setCapturedPiece(nullptr);
        } else if (move.getPromotedPawn() != nullptr) {
            delete move.getPromotedPawn();
            move.setPromotedPawn(nullptr);
        }
    }
    board->getMoveStack().clear();
    //delete scoreBoard and board and players
    delete scoreBoard;
    delete board;
    scoreBoard = nullptr;
    currentPlayer = nullptr;

    if (player1 != nullptr) {
        delete player1;
    }
    if (player2 != nullptr) {
        delete player2;
    }
    player1 = nullptr;
    player2 = nullptr;
}

void Controller::displayScore() {
    scoreBoard->displayScore();
}

bool Controller::getGameEnded() {
    return gameEnded;
}

bool Controller::getGameStarted() {
    return gameStarted;
}

Colour Controller::getStartTurnColour() {
    return startTurnColour;
}

void Controller::setStartTurnColour(Colour colour) {
    startTurnColour = colour;
}

Player *Controller::getCurrentPlayer() {
    return currentPlayer;
}

std::string Controller::coordinateToChessNotation(int x, int y) {
    // convert x and y coordinates to chess notation coordinates
    std::string notation;
    notation += 'a' + x; 
    notation += std::to_string(1 + y);
    return notation;
}

void Controller::printLatestMove(const std::vector<Move>& getMoveStack) {
    if (!getMoveStack.empty()) {
        const auto& move = getMoveStack.back();
        std::string fromNotation = coordinateToChessNotation(move.getFrom()->getX(), move.getFrom()->getY());
        std::string toNotation = coordinateToChessNotation(move.getTo()->getX(), move.getTo()->getY());

        std::cout << "Here is the latest move: "
                  << "\"" << fromNotation << "\" to \"" << toNotation << "\""
                  << std::endl;
    } else {
        std::cout << "No moves available." << std::endl;
    }
}

Square *Controller::stringToSquare(std::string squarestring) {
    //convert string coordinate input to square

    if (squarestring.length() != 2) {
        return nullptr;
    }

    char file = squarestring[0];
    char rank = squarestring[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return nullptr;
    }
    //ascii conversion
    int x = file - 'a';
    int y = rank - '1';
    return board->getSquare(x, y);
}

void Controller::setScoreBoard(ScoreBoard *sb) {
    scoreBoard = sb;
}

void Controller::setPromotedTo(std::string promotedType) {
    promotedTo = promotedType;
}

void Controller::handleCommand(const std::string &command) {
    //parse the command and execute the appropriate action
    //if the command is invalid, print an error message
    std::istringstream iss(command);
    std::string action, extra;
    iss >> action;

    if (action == "") {
        return;
    }

    if (action == "game") {
        if (gameStarted) {
            std::cout << "Game has already started!" << std::endl;
            return;
        }
        std::string whitePlayerType;
        std::string blackPlayerType;
        iss >> whitePlayerType >> blackPlayerType >> extra;

        if (extra != "") {
            std::cout << "Invalid command!" << std::endl;
            return;
        }

        // check if player types are valid and create the players
        if (whitePlayerType == "human") {
            player1 = new Human(Colour::White);
        } else if (whitePlayerType == "computer1") {
            player1 = new LevelOne(Colour::White, board);
        } else if (whitePlayerType == "computer2") {
            player1 = new LevelTwo(Colour::White, board);
        } else if (whitePlayerType == "computer3") {
            player1 = new LevelThree(Colour::White, board);
        } else if (whitePlayerType == "computer4") {
            player1 = new LevelFour(Colour::White, board);
        } else {
            std::cout << "Invalid player type!" << std::endl;
            return;
        }

        if (blackPlayerType == "human") {
            player2 = new Human(Colour::Black);
        } else if (blackPlayerType == "computer1") {
            player2 = new LevelOne(Colour::Black, board);
        } else if (blackPlayerType == "computer2") {
            player2 = new LevelTwo(Colour::Black, board);
        } else if (blackPlayerType == "computer3") {
            player2 = new LevelThree(Colour::Black, board);
        } else if (blackPlayerType == "computer4") {
            player2 = new LevelFour(Colour::Black, board);
        } else {
            std::cout << "Invalid player type!" << std::endl;
            return;
        }
        // start the game
        startGame(*player1, *player2);
    } else if (action == "resign") {
        if (!gameStarted) {
            std::cout << "Game has not started yet!" << std::endl;
            return;
        }
        iss >> extra;

        if (extra != "") {
            std::cout << "Invalid command!" << std::endl;
            return;
        }
        // end the game
        endGame(true);
        return;
    } else if (action == "move") {
        if (!gameStarted) {
            std::cout << "Game has not started yet!" << std::endl;
            return;
        }
        std::string from, to, promotePiece;
        iss >> from >> to >> promotePiece >> extra;

        // check if current player is human
        if (currentPlayer->isRobot() && from != "") {
            std::cout << "Invalid command! Robot will not take in coordinates." << std::endl;
            return;
        }

        //register what a pawn promotes to
        if (promotePiece != "") {
            setPromotedTo(promotePiece);
        }
        if ((!currentPlayer->isRobot()) && (from.length() != 2 || to.length() != 2)) {
            std::cout << "Invalid command!" << std::endl;
            return;
        }
        if (currentPlayer == nullptr) {
            std::cout << "No current player!" << std::endl;
        }

        //register a move from the player
        Move move = currentPlayer->makeMove(*board, from, to, promotePiece);
        //if the player is a robot and the move is a promotion and what the pawn promotes to
        if (currentPlayer->isRobot() && (move.getPromotedTo() == 'q' || move.getPromotedTo() == 'n' || move.getPromotedTo() == 'b' || move.getPromotedTo() == 'r')) {
            string s;
            s.push_back(move.getPromotedTo());
            setPromotedTo(s);
        }

        //moves a piece that is on a square
        if (move.getFrom() == nullptr || move.getTo() == nullptr) {
            std::cout << "Invalid move" << std::endl;
            return;
        }
        //play the move
        runGame(move);

    } else if (action == "setup") {
        setupMode();
    } else if (action == "undo") {
        if (board->getMoveStack().size() == 0) {
            std::cout << "No moves to undo!" << std::endl;
            return;
        }
        board->undoMove();
        std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << " called undo." << std::endl;
        //switch the current player
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
        //display the board
        board->notifyObservers();
    } else if (action == "history") {
        printLatestMove(board->getMoveStack());
    } else if (action == "score") {
        displayScore();
    } else {
        std::cout << "Invalid command!" << std::endl;
    }
}

void Controller::startGame(Player &p1, Player &p2) {
    //attribute and flag setup
    player1 = &p1;
    player2 = &p2;
    board->getMoveStack().clear();
    gameEnded = false;
    gameStarted = true;
    std::cout << "Game started!" << std::endl;
    //display the board
    board->notifyObservers();
    if (getStartTurnColour() == Colour::White) {
        currentPlayer = player1;
        std::cout << "It is player 1's turn..." << std::endl;
    } else if (getStartTurnColour() == Colour::Black) {
        currentPlayer = player2;
        std::cout << "It is player 2's turn..." << std::endl;
    }
}

void Controller::checkWin() {
    //check if the current player is in check or checkmate
    Colour colour = (currentPlayer == player1) ? Colour::White : Colour::Black;
    bool isInCheck = board->isInCheck(colour);

    if (isInCheck) {
        bool checkmate = board->isCheckmate(colour);
        if (checkmate) {
            gameEnded = true;

            if (currentPlayer == player1) {
                Colour color = player1->getColour();
            } else if (currentPlayer == player2) {
                Colour color = player2->getColour();
            }

            std::cout << "Checkmate! " << (currentPlayer == player1 ? "Black" : "White") << " wins! Game ended!" << std::endl;
            endGame(false);
        } else {
            std::cout << "Check!" << std::endl;
        }
    } else {
        bool stalemate = board->isStalemate(colour);
        if (stalemate) {
            gameEnded = true;
            endGame(false);
        }
    }
}

void Controller::runGame(const Move &move) {
    if (gameEnded) {
        std::cout << "No game in progress!" << std::endl;
        return;
    }
    //make a move on the board
    bool legal = board->movePiece(move);
    if (!legal) {
        return;
    }
    std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << " made a move." << std::endl;
    std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << "'s turn...." << std::endl;
    //switch the current player
    currentPlayer = (currentPlayer->getColour() == White) ? player2 : player1;
    checkWin();
}

void Controller::endGame(bool resigned) {
    gameEnded = true;
    gameStarted = false;
    //if the game is resigned, the player who resigned loses
    if (resigned) {
        if (currentPlayer == player1) {
            Colour color = player1->getColour();
        } else if (currentPlayer == player2) {
            Colour color = player2->getColour();
        }
        std::cout << "Player " << (currentPlayer == player1 ? "Black" : "White") << " wins!" << std::endl;
        std::cout << "Game ended!" << std::endl;
    }
    if (currentPlayer == player1) {
        scoreBoard->updateScore(false);
    } else {
        scoreBoard->updateScore(true);
    }
    //if the game is not resigned, check if the game is in checkmate or stalemate
    if (board->isCheckmate(currentPlayer->getColour())) {
        std::cout << "Checkmate! Player " << (currentPlayer == player1 ? "2" : "1") << " wins! Game ended!" << std::endl;
        if (currentPlayer == player1) {
            scoreBoard->updateScore(false);
        } else {
            scoreBoard->updateScore(true);
        }
    } else if (board->isStalemate(currentPlayer->getColour())) {
        std::cout << "Stalemate! Game ended!" << std::endl;
        scoreBoard->stalemateUpdate();
    }
    //reset the board and reset the players
    board->clearBoard();
    currentPlayer = nullptr;
    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;
    board->setupInitialBoard();
}

void Controller::setupMode() {
    if (gameStarted) {
        std::cout << "Game has already started, you can't setup now!" << std::endl;
        return;
    }
    //wipe the pieces
    board->clearBoard();
    board->notifyObservers();
    
    while (!getGameStarted()) {
        //custom board setup as per project guidelines
        cout << "> ";
        std::string command;
        std::cin >> command;
        if (command == "+") {
            std::string piece, square;
            std::cin >> piece >> square;
            
            //command checking
            if (piece.length() != 1 || square.length() != 2) {
                std::cout << "Invalid command! (Make sure you follow the right format)" << std::endl;
                continue;
            }

            Square *targetSquare = stringToSquare(square);
            if (targetSquare == nullptr) {
                std::cout << "Invalid square! (Out of Bounds)" << std::endl;
                continue;
            }

            if (targetSquare->getX() < 0 || targetSquare->getX() > 7 || targetSquare->getY() < 0 || targetSquare->getY() > 7) {
                std::cout << "Invalid square! (Out of Bounds)" << std::endl;
                continue;
            }

            //delete the piece if it exists on the square
            if (targetSquare != nullptr) {
                targetSquare->deletePiece();
            }

            //create a new piece and add it to the board based off input
            Colour colour = (piece[0] < 'a') ? Colour::White : Colour::Black;
            Piece *piecePtr = nullptr;
            if ((piece[0] == 'K' || piece[0] == 'k') && board->findKing(colour) == nullptr) {
                piecePtr = new King(colour);
            } else if ((piece[0] == 'Q' || piece[0] == 'q')) {
                piecePtr = new Queen(colour);
            } else if ((piece[0] == 'R' || piece[0] == 'r')) {
                piecePtr = new Rook(colour);
            } else if (piece[0] == 'B' || piece[0] == 'b') {
                piecePtr = new Bishop(colour);
            } else if (piece[0] == 'N' || piece[0] == 'n') {
                piecePtr = new Knight(colour);
            } else if (piece[0] == 'P' || piece[0] == 'p') {
                piecePtr = new Pawn(colour);
            } else {
                std::cout << "Invalid piece!" << std::endl;
                continue;
            }
            targetSquare->setPiece(piecePtr);
            board->addPiece(piecePtr, targetSquare);
            piecePtr->setBoard(board);
            board->notifyObservers();
        }
        //remove a piece from the board at target square
        else if (command == "-") {
            std::string square;
            std::cin >> square;

            if (square.length() != 2) {
                std::cout << "Invalid command! (Make sure to it is in proper format)" << std::endl;
                continue;
            }
            Square *targetSquare = stringToSquare(square);
            if (targetSquare == nullptr) {
                std::cout << "Invalid square!" << std::endl;
                continue;
            }

            int x = targetSquare->getX();
            int y = targetSquare->getY();
            if ((board->getSquare(x, y)) && board->getSquare(x, y)->getPiece() == nullptr) {
                std::cout << "No piece to remove here!" << std::endl;
            }

            board->removePiece(targetSquare);
            board->notifyObservers();
        }
        //set the starting turn colour
        else if (command == "=") {
            std::string colour;
            std::cin >> colour;
            if (colour == "white") {
                setStartTurnColour(Colour::White);
                std::cout << "Player 1 will start! (White)" << std::endl;
            } else if (colour == "black") {
                setStartTurnColour(Colour::Black);
                std::cout << "Player 2 will start! (Black)" << std::endl;
            } else {
                std::cout << "Invalid colour!" << std::endl;
                continue;
            }
        } else if (command == "done") {
            if (board == nullptr) {
                std::cout << "No board!" << std::endl;
                continue;
            }
            if (board->isValidSetup()) {
                std::cout << "Setup complete...you can play as normal now (don't forget to start a game)!" << std::endl;
                return;
            } else {
                std::cout << "Invalid setup! " << std::endl;
                std::cout << "Please make sure both kings are on the board, not in check and no pawns are on the end rows." << std::endl;
            }
        } else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
}
