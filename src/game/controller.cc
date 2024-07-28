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
// #include "robot.h"
#include "rook.h"
#include "square.h"
#include "textobserver.h"
#include "graphicsobserver.h"

Controller::Controller(Player *player1, Player *player2) : player1(player1), player2(player2), currentPlayer(player1), gameEnded(false) {
    board = new Board();
    board->setController(this);

    // for now -- only textdisplay
    new TextObserver(*board);
    // new GraphicsObserver(*board);
}

bool Controller::getGameEnded() {
    return gameEnded;
}

void Controller::setGameEnded(bool ended) {
    gameEnded = ended;
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
    std::string action;
    while (iss >> action) {
        if (action == "game") {
        std::string whitePlayerType;
        std::string blackPlayerType;
        iss >> whitePlayerType >> blackPlayerType;

        if (whitePlayerType == "human") {
            player1 = new Human(Colour::White);
        // } else if (whitePlayerType == "computer1") {
        //     player1 = new Robot(Colour::White, 1);
        // } else if (whitePlayerType == "computer2") {
        //     player1 = new Robot(Colour::White, 2);
        // } else if (whitePlayerType == "computer3") {
        //     player1 = new Robot(Colour::White, 3);
        }

        if (blackPlayerType == "human") {
            player2 = new Human(Colour::Black);
        // } else if (blackPlayerType == "computer1") {
        //     player2 = new Robot(Colour::Black, 1);
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
            iss >> from >> to >> promotePiece;
            if (promotePiece != "") {
                setPromotedTo(promotePiece);
            }
            Square *fromSquare = stringToSquare(from);
            Square *toSquare = stringToSquare(to);

            Move move = Move(fromSquare, toSquare);
            runGame(*player1, *player2, move);
        } else if (action == "setup") {
            setupMode();
        }
    }
}

void Controller::startGame(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;
    currentPlayer = player1;
    gameEnded = false;
    MoveHistory.clear();
    std::cout << "Game started! (between Player 1 and Player2)" << std::endl;

    // display via text display
    board->notifyObservers();
}

void Controller::checkWin() {
    std::cout << "checkWin" << std::endl;
    Colour colour = currentPlayer->getColour();
    std::cout << "colour: " << colour << std::endl;

    bool checkmate = board->isCheckmate(colour);
    // std::cout << "checkmate done" << std::endl;
    bool stalemate = board->isStalemate(colour);
    // std::cout << "stalemate done" << std::endl;
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
    } else if (stalemate) {
        gameEnded = true;
        std::cout << "Stalemate!" << std::endl;
    }
}

void Controller::playTurn(Player *p) {
    Move move = p->makeMove(*board);
    board->movePiece(move);
    MoveHistory.push_back(move);
    std::cout << "Player " << (p == player1 ? "1" : "2") << " made a move" << std::endl;
}

void Controller::runGame(Player &p1, Player &p2, const Move &move) {
    // Move move = currentPlayer->makeMove(*board);
    board->movePiece(move);
    MoveHistory.push_back(move);
    std::cout << "Player " << (currentPlayer == player1 ? "1" : "2") << " made a move" << std::endl;
    checkWin();
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
    board->notifyObservers();
}

void Controller::endGame(bool resigned) {
    gameEnded = true;
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
    while (getGameEnded()) {
        board->clearBoard();
        std::string command;
        std::cin >> command;

        if (command == "+") {
            std::string piece, square;
            std::cin >> piece >> square;

            Square *targetSquare = stringToSquare(square);
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
            if (piece[1] == 'K' || piece[1] == 'k') {
                pieceType = PieceType::king;
                piecePtr = new King(colour);
            } else if (piece[1] == 'Q' || piece[1] == 'q') {
                pieceType = PieceType::queen;
                piecePtr = new Queen(colour);
            } else if (piece[1] == 'R' || piece[1] == 'r') {
                pieceType = PieceType::rook;
                piecePtr = new Rook(colour);
            } else if (piece[1] == 'B' || piece[1] == 'b') {
                pieceType = PieceType::bishop;
                piecePtr = new Bishop(colour);
            } else if (piece[1] == 'N' || piece[1] == 'n') {
                pieceType = PieceType::knight;
                piecePtr = new Knight(colour);
            } else if (piece[1] == 'P' || piece[1] == 'p') {
                pieceType = PieceType::pawn;
                piecePtr = new Pawn(colour);
            } else {
                std::cout << "Invalid piece" << std::endl;
                continue;
            }
            targetSquare->setPiece(piecePtr);
        }

        else if (command == "-") {
            std::string square;
            std::cin >> square;
            Square *targetSquare = stringToSquare(square);
            if (targetSquare == nullptr) {
                std::cout << "No piece to remove here" << std::endl;
                continue;
            }
            board->removePiece(targetSquare);
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
            if (board->isValidSetup()) {
                gameEnded = false;
                std::cout << "Setup complete" << std::endl;
            } else {
                std::cout << "Invalid setup" << std::endl;
            }
        }

        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}