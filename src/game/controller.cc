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
#include "robotLevelTwo.h"
#include "robotLevelThree.h"
#include "scoreboard.h"
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

void Controller::displayScore() {
    scoreBoard->displayScore();
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

Colour Controller::getStartTurnColour() {
    return startTurnColour;
}

void Controller::setStartTurnColour(Colour colour) {
    startTurnColour = colour;
}

Player *Controller::getCurrentPlayer() {
    return currentPlayer;
}

Square *Controller::stringToSquare(std::string squarestring) {

    if (squarestring.length() != 2) {
        return nullptr;
    }

    char file = squarestring[0];
    char rank = squarestring[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return nullptr;
    }
    int x = file - 'a';
    int y = rank - '1';
    return board->getSquare(x, y);
}

void Controller::setScoreBoard(ScoreBoard *sb) {
    scoreBoard = sb;
}

// PieceType Controller::getPromotedTo() {
//     if (promotedTo == "Q" || promotedTo == "q") {
//         return PieceType::queen;
//     } else if (promotedTo == "R" || promotedTo == "r") {
//         return PieceType::rook;
//     } else if (promotedTo == "B" || promotedTo == "b") {
//         return PieceType::bishop;
//     } else if (promotedTo == "N" || promotedTo == "n") {
//         return PieceType::knight;
//     }
//     return PieceType::pawn;
// }

void Controller::setPromotedTo(std::string promotedType) {
    promotedTo = promotedType;
}

void Controller::handleCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string action, extra;
    iss >> action;
        if (action == "game") {
            if (gameStarted) {
                std::cout << "Game has already started" << std::endl;
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
            } else if (whitePlayerType == "computer2") {
                player1 = new LevelTwo(Colour::White, board);
            // } else if (whitePlayerType == "computer3") {
            //     player1 = new Robot(Colour::White, 3);
            }
            else {
                std::cout << "Invalid player type" << std::endl;
                return;
            }

            if (blackPlayerType == "human") {
                player2 = new Human(Colour::Black);
            } else if (blackPlayerType == "computer1") {
                player2 = new LevelOne(Colour::Black, board);
            } else if (blackPlayerType == "computer2") {
                player2 = new LevelTwo(Colour::Black, board);
            // } else if (blackPlayerType == "computer3") {
            //     player2 = new Robot(Colour::Black, 3);
            }
            else {
                std::cout << "Invalid player type" << std::endl;
                return;
            }
            startGame(*player1, *player2);
        } else if (action == "resign") {

            if (!gameStarted) {
                std::cout << "Game has not started yet" << std::endl;
                return;
            }
            iss >> extra;

            if (extra != "") {
                std::cout << "Invalid command - extra commands found" << std::endl;
                return;
            }
            endGame(true);
            return;
        } else if (action == "move") {
            if (!gameStarted) {
                std::cout << "Game has not started yet" << std::endl;
                return;
            }
            std::string from, to, promotePiece;
            iss >> from >> to >> promotePiece >> extra;

            //check if current player is human
            if (currentPlayer->isRobot() && from != "") {
                std::cout << "Invalid command" << std::endl;
                return;
            }

            if (promotePiece != "") {
                setPromotedTo(promotePiece);
            }
            if ((!currentPlayer->isRobot()) && (from.length() != 2 || to.length() != 2)) {
                std::cout << "Invalid command" << std::endl;
                return;
            }
            if (currentPlayer == nullptr) {
                std::cout << "No current player" << std::endl;
            }
            Move move = currentPlayer->makeMove(*board, from, to, promotePiece);

            if (currentPlayer->isRobot() && (move.getPromotedTo() == 'q' || move.getPromotedTo() == 'n' || move.getPromotedTo() == 'b' || move.getPromotedTo() == 'r')) {
                string s;
                s.push_back(move.getPromotedTo());
                setPromotedTo(s);
            }

            if(move.getFrom() == nullptr || move.getTo() == nullptr) {
                std::cout << "Invalid move" << std::endl;
                return;
            }
            // Move move = Move(fromSquare, toSquare);
            runGame(move);

            } else if (action == "setup") {
                setupMode();
            } else if (action == "undo") { // not necessary, but we still have it
                if (MoveHistory.size() == 0) {
                    std::cout << "No moves to undo" << std::endl;
                    return;
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

void Controller::startGame(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;
    MoveHistory.clear();
    gameEnded = false;
    gameStarted = true;
    std::cout << "Game started! (between Player 1 and Player2)" << std::endl;
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
    Colour colour = (currentPlayer == player1) ? Colour::White : Colour::Black;
    bool isInCheck = board->isInCheck(colour);

    if (isInCheck) {
        std::cout << (colour == White ? "White" : "Black") << " is in check!" << std::endl;
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

void Controller::runGame(const Move &move) {
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
    std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << "'s turn...." << std::endl;
    currentPlayer = (currentPlayer->getColour() == White) ? player2 : player1;
    checkWin();
}

void Controller::endGame(bool resigned) {
    gameEnded = true;
    gameStarted = false;
    if (resigned) {
        std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << " wins!" << std::endl;
        std::cout << "Game ended!" << std::endl;
    }
    if (currentPlayer == player1) {
        scoreBoard->updateScore(true);
    } else {
        scoreBoard->updateScore(false);
    }
    currentPlayer == player1 ? player2 : player1;
    board->setupInitialBoard();
}

void Controller::setupMode() {
    if (gameStarted) {
        std::cout << "Game has already started, you can't setup now" << std::endl;
        return;
    }
    board->clearBoard();
    board->notifyObservers();
    while (!getGameStarted()) {
        std::string command;
        std::cin >> command;
        if (command == "+") {
            std::string piece, square;
            std::cin >> piece >> square;

            if (piece.length() != 1 || square.length() != 2) {
                std::cout << "Invalid command (Make sure you follow the right format)" << std::endl;
                continue;
            }

            Square *targetSquare = stringToSquare(square);
            if (targetSquare == nullptr) {
                std::cout << "Invalid square (Out of Bounds)" << std::endl;
                continue;
            }

            if (targetSquare->getX() < 0 || targetSquare->getX() > 7 || targetSquare->getY() < 0 || targetSquare->getY() > 7) {
                std::cout << "Invalid square (Out of Bounds)" << std::endl;
                continue;
            }

            if (targetSquare != nullptr) {
                targetSquare->deletePiece();
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
            board->notifyObservers();
        }

        else if (command == "-") {
            std::string square;
            std::cin >> square;

            if (square.length() != 2) {
                std::cout << "Invalid command (Make sure to it is in proper format)" << std::endl;
                continue;
            }
            Square *targetSquare = stringToSquare(square);
            if (targetSquare == nullptr) {
                std::cout << "Invalid square" << std::endl;
                continue;
            }

            int x = targetSquare->getX();
            int y = targetSquare->getY();
            if ((board->getSquare(x, y)) && board->getSquare(x, y)->getPiece() == nullptr) {
                std::cout << "No piece to remove here" << std::endl;
            }

            board->removePiece(targetSquare);
            board->notifyObservers();
        }

        else if (command == "=") {
            std::string colour;
            std::cin >> colour;
            if (colour == "white") {
                setStartTurnColour(Colour::White);
                std::cout << "starting turn colour set to player 1 (white)" << std::endl;
            } else if (colour == "black") {
                setStartTurnColour(Colour::Black);
                std::cout << "starting turn colour set to player 2 (black)" << std::endl;
            } else {
                std::cout << "Invalid colour" << std::endl;
                continue;
            }
        }
        else if (command == "done") {
            if (board == nullptr) {
                std::cout << "No board" << std::endl;
                continue;
            }
            if (board->isValidSetup()) {
                std::cout << "Setup complete...you can play as normal now (don't forget to start a game)!" << std::endl;
                return;
            } else {
                std::cout << "Invalid setup... " << std::endl;
                std::cout << "Please make sure both kings are on the board and not in check" << std::endl;
            }
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}
