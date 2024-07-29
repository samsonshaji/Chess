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

Controller::Controller(Player *player1, Player *player2) : player1(player1), player2(player2), currentPlayer(player1), gameEnded(false) {
    board = new Board();
    board->setController(this);
    scoreBoard = new ScoreBoard();
    new TextObserver(*board);
    // new GraphicsObserver(*board);
}

bool Controller::getGameEnded() {
    return gameEnded;
}

void Controller::setGameEnded(bool ended) {
    gameEnded = ended;
}

bool Controller::getGameStarted() {
    return gameStarted;
}

void Controller::setGameStarted(bool started) {
    gameStarted = started;
}

Square *Controller::stringToSquare(std::string squarestring) {
    // std::cout << "THIS SHOUDL PRINT PRINTED RIGHT BEFORE GET SQUARE2" << std::endl;
    // std::cout << "squarestring: " << squarestring << std::endl;
    if (squarestring.length() != 2) {
        return nullptr;
    }
    // std::cout << "THIS SHOUDL PRINT PRINTED RIGHT BEFORE GET SQUARE1" << std::endl;

    char file = squarestring[0];
    char rank = squarestring[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return nullptr;
    }
    // std::cout << "THIS SHOUDL PRINT PRINTED RIGHT BEFORE GET SQUARE5" << std::endl;
    // find corresponding square in board
    int x = file - 'a';
    int y = rank - '1';
    return board->getSquare(x, y);
}

void Controller::setScoreBoard(ScoreBoard *sb) {
    scoreBoard = sb;
}

PieceType Controller::getPromotedTo() {
    if (promotedTo == "Q" || promotedTo == "q") {
        return PieceType::queen;
    } else if (promotedTo == "R" || promotedTo == "r") {
        return PieceType::rook;
    } else if (promotedTo == "B" || promotedTo == "b") {
        return PieceType::bishop;
    } else if (promotedTo == "N" || promotedTo == "n") {
        return PieceType::knight;
    }
    return PieceType::pawn;
}

void Controller::setPromotedTo(std::string promotedType) {
    promotedTo = promotedType;
}

void Controller::handleCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string action, extra;
    while (iss >> action){
        if (action == "game") {
            std::string whitePlayerType;
            std::string blackPlayerType;
            iss >> whitePlayerType >> blackPlayerType >> extra;

            if (gameStarted) {
                std::cout << "Game has already started" << std::endl;
                break;
            }

            if (whitePlayerType == "human") {
                player1 = new Human(Colour::White);
            } else if (whitePlayerType == "computer1") {
                player1 = new LevelOne(Colour::White, board);
            // } else if (whitePlayerType == "computer2") {
            //     player1 = new Robot(Colour::White, 2);
            // } else if (whitePlayerType == "computer3") {
            //     player1 = new Robot(Colour::White, 3);
            }

            if (blackPlayerType == "human") {
                player2 = new Human(Colour::Black);
            } else if (blackPlayerType == "computer1") {
                player2 = new LevelOne(Colour::Black, board);
            // } else if (blackPlayerType == "computer2") {
            //     player2 = new Robot(Colour::Black, 2);
            // } else if (blackPlayerType == "computer3") {
            //     player2 = new Robot(Colour::Black, 3);
            }
            startGame(*player1, *player2);
        } else if (action == "resign") {
            endGame(true);
            break;
        } else if (action == "move") {
            std::string from, to, promotePiece;
            iss >> from >> to >> promotePiece >> extra;
            if (promotePiece != "") {
                setPromotedTo(promotePiece);
            }

            Move move = currentPlayer->makeMove(*board, from, to, promotePiece);
            // Move move = Move(fromSquare, toSquare);
            runGame(*player1, *player2, move);

            } else if (action == "setup") {
                setupMode();
            } else if (action == "undo") { // not necessary, but we still have it
                if (MoveHistory.size() == 0) {
                    std::cout << "No moves to undo" << std::endl;
                    continue;
                }
                board->undoMove();
                MoveHistory.pop_back();
                std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << " called undo" << std::endl;
                currentPlayer = (currentPlayer == player1) ? player2 : player1;
                board->notifyObservers();
            } else {
                std::cout << "Invalid command" << std::endl;
            }
    }
}

void Controller::startGame(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;
    currentPlayer = player1;
    gameEnded = false;
    MoveHistory.clear();
    gameStarted = true;
    std::cout << "Game started! (between Player 1 and Player2)" << std::endl;

    // display via text display
    board->notifyObservers();
}

void Controller::checkWin() {
    Colour colour = (currentPlayer == player1) ? Colour::White : Colour::Black;
    bool isInCheck = board->isInCheck(colour);

    if (isInCheck) {
        bool checkmate = board->isCheckmate(colour);
        if (checkmate) {
            gameEnded = true;
            
            std::cout << "Checkmate! ";
            if (currentPlayer == player1) {
                std::cout << "Player 2 wins!" << std::endl;
                return;
            } else {
                std::cout << "Player 1 wins!" << std::endl;
                return;
            }
        } else {
            std::cout << "Check!" << std::endl;
        }
    }
    else {
        bool stalemate = board->isStalemate(colour);
        if (stalemate) {
            gameEnded = true;
            std::cout << "Stalemate!" << std::endl;
        }
    }
}

void Controller::runGame(Player &p1, Player &p2, const Move &move) {
    // Move move = currentPlayer->makeMove(*board);
    if (gameEnded){
        std::cout << "Game has ended, who you think you foolin?" << std::endl;
        return;
    }
    bool legal = board->movePiece(move);
    if (!legal) {
        return;
    }
    MoveHistory.push_back(move);
    std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << " made a move" << std::endl;
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
    checkWin();
}

void Controller::endGame(bool resigned) {
    gameEnded = true;
    gameStarted = false;
    if (resigned) {
        std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << " wins!" << std::endl;
        std::cout << "Game ended!" << std::endl;
    }
    currentPlayer == player1 ? player2 : player1;
    if (currentPlayer == player1) {
        scoreBoard->updateScore(true);
    } else {
        scoreBoard->updateScore(false);
    }
}

void Controller::setupMode() {
    if (gameStarted) {
        std::cout << "Game has already started, you can't setup now" << std::endl;
        return;
    }
    board->clearBoard();
    board->print();
    while (!getGameStarted()) {
        std::string command;
        std::cin >> command;
        if (command == "+") {
            std::string piece, square;
            std::cin >> piece >> square;

            // std::cout << "piece[0]" << piece[0] << std::endl;
            // std::cout << "piece[1]" << square << std::endl;

            Square *targetSquare = stringToSquare(square);
            std::cout << "targetSquare: " << targetSquare->getPiece() << std::endl;
            std::cout << "targetSquare x and y :  " << targetSquare->getX() << " " << targetSquare->getY() << std::endl;

            int x = targetSquare->getX();
            int y = targetSquare->getY();

            if (board->getSquare(x, y) && board->getSquare(x, y)->getPiece() == nullptr) {
                std::cout << "SAMSON BRO YOU ARE RIGHT" << std::endl;
            }
            if (targetSquare != nullptr) {
                targetSquare->deletePiece();
            }
            if (targetSquare->getX() < 0 || targetSquare->getX() > 7 || targetSquare->getY() < 0 || targetSquare->getY() > 7) {
                std::cout << "Invalid square" << std::endl;
                continue;
            }

            Colour colour = (piece[0] < 'a') ? Colour::White : Colour::Black;
            PieceType pieceType;
            Piece *piecePtr = nullptr;
            if ((piece[0] == 'K' || piece[0] == 'k') && board->findKing(colour) == nullptr) {
                pieceType = PieceType::king;
                piecePtr = new King(colour);
            } else if ((piece[0] == 'Q' || piece[0] == 'q')) {
                pieceType = PieceType::queen;
                piecePtr = new Queen(colour);
            } else if ((piece[0] == 'R' || piece[0] == 'r')) {
                pieceType = PieceType::rook;
                piecePtr = new Rook(colour);
            } else if (piece[0] == 'B' || piece[0] == 'b') {
                pieceType = PieceType::bishop;
                piecePtr = new Bishop(colour);
            } else if (piece[0] == 'N' || piece[0] == 'n') {
                pieceType = PieceType::knight;
                piecePtr = new Knight(colour);
            } else if (piece[0] == 'P' || piece[0] == 'p') {
                pieceType = PieceType::pawn;
                piecePtr = new Pawn(colour);
            } else {
                std::cout << "Invalid piece" << std::endl;
                continue;
            }
            targetSquare->setPiece(piecePtr);
            board -> addPiece(piecePtr, targetSquare);
            piecePtr->setBoard(board);
            // std::cout << "NOTIFYING OBSERVERS BELOW THIS" << std::endl;
            // std::cout << " ___________________ ___________________" << std::endl;
            board->notifyObservers();
        }

        else if (command == "-") {
            // std::cout << "INSide the function here " << std::endl;
            std::string square;
            std::cin >> square;
            Square *targetSquare = stringToSquare(square);

            // if (targetSquare == nullptr) {
            //     std::cout << "Invalid square" << std::endl;
            //     continue;
            // }
            int x = targetSquare->getX();
            int y = targetSquare->getY();
            std::cout << "x and y: " << x << " " << y << std::endl;
            std::cout << "Right before remove piece" << std::endl;

            if ((board->getSquare(x, y)) && board->getSquare(x, y)->getPiece() == nullptr) {
                std::cout << "No piece to remove here" << std::endl;
            }
            std::cout << "Right before remove piece" << std::endl;
            board->removePiece(targetSquare);
            board->notifyObservers();
        }

        else if (command == "=") {
            std::string colour;
            std::cin >> colour;
            if (colour == "white") {
                currentPlayer = player1;
            } else if (colour == "black") {
                currentPlayer = player2;
            } else {
                std::cout << "Invalid colour" << std::endl;
            }
        }

        else if (command == "done") {
            if (board == nullptr) {
                std::cout << "No board" << std::endl;
                continue;
            }
            if (board->isValidSetup()) {
                gameEnded = false;
                std::cout << "Setup complete..you can play as normal now!" << std::endl;
                gameStarted = true;
                return;
            } else {
                std::cout << "Invalid setup.. " << std::endl;
                std::cout << "Please make sure both kings are on the board and not in check" << std::endl;
            }
        }

        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}
