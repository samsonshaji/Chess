#include <iostream>
#include <sstream>

#include "bishop.h"
#include "board.h"
#include "controller.h"
#include "human.h"
#include "king.h"
#include "knight.h"
#include "move.h"
#include "pawn.h"
#include "queen.h"
#include "robot.h"
#include "robotLevelOne.h"
#include "rook.h"
#include "square.h"
#include "textobserver.h"
#include "graphicsobserver.h"

Controller::Controller(Player *player1, Player *player2) : player1(player1), player2(player2), currentPlayer(player1) {
    board = new Board();
    board->setController(this);

    // for now -- only textdisplay
    new TextObserver(*board);
    // new GraphicsObserver(*board);
}

Player *Controller::getCurrentPlayer() const {
    return currentPlayer;
}

bool Controller::getGameStarted() {
    return gameStarted;
}

void Controller::setGameStarted(bool started) {
    gameStarted = started;
}

void Controller::setScoreBoard(ScoreBoard *sb) {
    scoreBoard = sb;
}

void Controller::handleCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string action, extra;
    iss >> action;
    if (action == "game") {

        if (getGameStarted()) {
            std::cout << "Game already in progress" << std::endl;
            return;
        }

        std::string whitePlayerType;
        std::string blackPlayerType;
        iss >> whitePlayerType >> blackPlayerType >> extra;

        if (extra != "") {
            std::cout << "Invalid command" << std::endl;
            return;
        }

        if (whitePlayerType == "human") {
            player1 = new Human(Colour::White);
        } else if (whitePlayerType == "computer1") {
            player1 = new LevelOne(Colour::White, board);
        }
        // } else if (whitePlayerType == "computer2") {
        //     player1 = new Robot(Colour::White, 2);
        // } else if (whitePlayerType == "computer3") {
        //     player1 = new Robot(Colour::White, 3);
        else {
            std::cout << "Invalid player type" << std::endl;
            return;
        }

        if (blackPlayerType == "human") {
            player2 = new Human(Colour::Black);
        } else if (blackPlayerType == "computer1") {
            player2 = new LevelOne(Colour::Black, board);
        }
        // } else if (blackPlayerType == "computer2") {
        //     player2 = new Robot(Colour::Black, 2);
        // } else if (blackPlayerType == "computer3") {
        //     player2 = new Robot(Colour::Black, 3);
        else {
            std::cout << "Invalid player type" << std::endl;
            return;
        }
        startGame(*player1, *player2);
    } else if (action == "resign") {

        if (!getGameStarted()) {
            std::cout << "No game currently in progress" << std::endl;
            return;
        }

        iss >> extra;

        if (extra != "") {
            std::cout << "Invalid command" << std::endl;
            return;
        }
        endGame(true);
    } else if (action == "move") {

        if(!getGameStarted()) {
            std::cout << "No game currently in progress" << std::endl;
            return;
        }

        std::string from, to, promoteTo;
        iss >> from >> to >> promoteTo >> extra;

        if (extra != "") {
            std::cout << "Invalid command" << std::endl;
            return;
        }

        Move move = currentPlayer->makeMove(*board, from, to, promoteTo);

        if (move.getMoveType() == MoveType::Invalid) {
            std::cout << "Invalid move" << std::endl;
            return;
        }

        playTurn(move);
    } else if (action == "setup") {

        if (getGameStarted()) {
            std::cout << "Game already in progress" << std::endl;
            return;
        }

        iss >> extra;
        
        if (extra != "") {
            std::cout << "Invalid command" << std::endl;
            return;
        }

        setupMode();
    }
    else {
        std::cout << "Invalid command" << std::endl;
        return;
    }
}

void Controller::startGame(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;

    if (!setUp){
        currentPlayer = player1;
    }
    setGameStarted(true);


    // display via text display
    board->notifyObservers();
    std::cout << "Game started! Player " << currentPlayer->getColour() + 1 << " turn..." << std::endl;
}

void Controller::checkWin() {
    Colour colour = currentPlayer->getColour();

    bool checkmate = board->isCheckmate(colour);
    bool stalemate = board->isStalemate(colour);
    
    if (checkmate) {
        std::cout << "Checkmate! ";
        if (currentPlayer == player1) {
            std::cout << "Player 2 wins!" << std::endl;
            return;
        } else {
            std::cout << "Player 1 wins!" << std::endl;
            return;
        }
    } else if (stalemate) {
        std::cout << "Stalemate!" << std::endl;
    }
}

void Controller::playTurn(const Move &move) {
    if(!board->movePiece(move)) {
        return;
    }
    std::cout << "Player " << currentPlayer->getColour() + 1 << " made a move." << std::endl;
    checkWin();
    currentPlayer = (currentPlayer->getColour() == Colour::White) ? player2 : player1;
    std::cout << "Player " << currentPlayer->getColour() + 1 << " turn..." << std::endl;
}

void Controller::endGame(bool resigned) {
    if (resigned) {
        std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << " wins!" << std::endl;
        std::cout << "Game ended!" << std::endl;
        return;
    }
    currentPlayer == player1 ? player2 : player1;
    if (currentPlayer == player1) {
        scoreBoard->updateScore(true);
    } else {
        scoreBoard->updateScore(false);
    }
    std::cout << "Game ended!" << std::endl;
}

void Controller::setupMode() {
    // while (getGameEnded()) {
    //     board->clearBoard();
    //     std::string command;
    //     std::cin >> command;

    //     if (command == "+") {
    //         std::string piece, square;
    //         std::cin >> piece >> square;

    //         Square *targetSquare = stringToSquare(square);
    //         if (targetSquare != nullptr) {
    //             targetSquare->deletePiece();
    //         }
    //         if (targetSquare->getX() < 0 || targetSquare->getX() > 7 || targetSquare->getY() < 0 || targetSquare->getY() > 7) {
    //             std::cout << "Invalid square" << std::endl;
    //             continue;
    //         }

    //         Colour colour = (piece[0] < 'a') ? Colour::White : Colour::Black;
    //         PieceType pieceType;
    //         Piece *piecePtr = nullptr;
    //         if (piece[1] == 'K' || piece[1] == 'k') {
    //             pieceType = PieceType::king;
    //             piecePtr = new King(colour);
    //         } else if (piece[1] == 'Q' || piece[1] == 'q') {
    //             pieceType = PieceType::queen;
    //             piecePtr = new Queen(colour);
    //         } else if (piece[1] == 'R' || piece[1] == 'r') {
    //             pieceType = PieceType::rook;
    //             piecePtr = new Rook(colour);
    //         } else if (piece[1] == 'B' || piece[1] == 'b') {
    //             pieceType = PieceType::bishop;
    //             piecePtr = new Bishop(colour);
    //         } else if (piece[1] == 'N' || piece[1] == 'n') {
    //             pieceType = PieceType::knight;
    //             piecePtr = new Knight(colour);
    //         } else if (piece[1] == 'P' || piece[1] == 'p') {
    //             pieceType = PieceType::pawn;
    //             piecePtr = new Pawn(colour);
    //         } else {
    //             std::cout << "Invalid piece" << std::endl;
    //             continue;
    //         }
    //         targetSquare->setPiece(piecePtr);
    //     }

    //     else if (command == "-") {
    //         std::string square;
    //         std::cin >> square;
    //         Square *targetSquare = stringToSquare(square);
    //         if (targetSquare == nullptr) {
    //             std::cout << "No piece to remove here" << std::endl;
    //             continue;
    //         }
    //         board->removePiece(targetSquare);
    //     }

    //     else if (command == "=") {
    //         std::string colour;
    //         std::cin >> colour;
    //         if (colour == "white") {
    //             currentPlayer = player1;
    //         } else if (colour == "black") {
    //             currentPlayer = player2;
    //         } else {
    //             std::cout << "Invalid colour" << std::endl;
    //         }
    //     }

    //     else if (command == "done") {
    //         if (board->isValidSetup()) {
    //             std::cout << "Setup complete" << std::endl;
    //         } else {
    //             std::cout << "Invalid setup" << std::endl;
    //         }
    //     }

    //     else {
    //         std::cout << "Invalid command" << std::endl;
    //     }
    // }
}