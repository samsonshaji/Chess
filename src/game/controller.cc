#include <iostream>
#include <sstream>

#include "controller.h"
#include "board.h"
#include "human.h"
#include "robot.h"
#include "move.h"

Controller::Controller(Player* player1, Player* player2) : 
player1(player1), player2(player2), currentPlayer(player1), gameEnded(false) {}

void Controller::setScoreBoard(ScoreBoard* sb) {
    scoreBoard = sb;
}

PieceType Controller::getPromotedTo() {
    if (promotedTo == "Q" || promotedTo == "q") {
        return PieceType::Queen;
    } else if (promotedTo == "R" || promotedTo == "r") {
        return PieceType::Rook;
    } else if (promotedTo == "B"  || promotedTo == "b") {
        return PieceType::Bishop;
    } else if (promotedTo == "N" || promotedTo == "n") {
        return PieceType::Knight;
    }
    return PieceType::Pawn;
}

void Controller::setPromotedTo(std::string promotedType) {
    promotedTo = promotedType;
}

void Controller::handleCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string action;
    iss >> action;

    if (command == "game") {
        std::string whitePlayerType;
        std::string blackPlayerType;
        std::cin >> whitePlayerType >> blackPlayerType;

        if (whitePlayerType == "human") {
            player1 = new Human(Colour::White);
        } else if (whitePlayerType == "computer1") {
            player1 = new Robot(Colour::White, 1);
        } else if (whitePlayerType == "computer2") {
            player1 = new Robot(Colour::White, 2);
        } else if (whitePlayerType == "computer3") {
            player1 = new Robot(Colour::White, 3);
        }

        if (blackPlayerType == "human") {
            player2 = new Human(Colour::Black);
        } else if (blackPlayerType == "computer1") {
            player2 = new Robot(Colour::Black, 1);
        } else if (blackPlayerType == "computer2") {
            player2 = new Robot(Colour::Black, 2);
        } else if (blackPlayerType == "computer3") {
            player2 = new Robot(Colour::Black, 3);
        }
        startGame(*player1, *player2);
    }
    else if (command == "resign") {
        endGame(true);
    } 
    else if (command == "move") {
        std::string from, to, promotePeice;
        iss >> from >> to >> promotePeice;
        if (promotePeice != "") {
            setPromotedTo(promotePeice);
        }
        Move move = Move(from, to);
        runGame(*player1, *player2);
    } 
    else if (command == "end") {
        return;
    }

}

void Controller::startGame(Player &p1, Player &p2) {
    player1 = &p1;
    player2 = &p2;
    currentPlayer = player1;
    gameEnded = false;
    board = Board();
    MoveHistory.clear();
    std::cout << "Game started! (between Player 1 and Player2)" << std::endl;
}

void Controller::checkWin() {
    if (board.isCheckmate(currentPlayer->getColour())) {
        gameEnded = true;
        std::cout << "Checkmate! ";
        if (currentPlayer == player1) {
            std::cout << "Player 2 wins!" << std::endl;
        } else {
            std::cout << "Player 1 wins!" << std::endl;
        }
    } else if (board.isStalemate(currentPlayer->getColour())) {
        gameEnded = true;
        std::cout << "Stalemate!" << std::endl;
    }
}

// newly added -> document later
void Controller::playTurn(Player* p) {
    Move move = p->makeMove(board);
    board.movePiece(move);
    MoveHistory.push_back(move);
    std::cout << "Player " << (p == player1 ? "1" : "2") << "made a move" << std::endl;
}

void Controller::runGame(Player &p1, Player &p2) {
    while (!gameEnded) {
        board.notifyObservers();
        playTurn(currentPlayer);
        checkWin();
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
}

void Controller::endGame(bool resigned) {
    gameEnded = true;
    if (resigned) {
        std::cout << "Player " << (currentPlayer == player1 ? "2" : "1") << " wins!" << std::endl;
    }
    currentPlayer == player1 ? player2 : player1;
    if (currentPlayer == player1) {
        scoreBoard->updateScore(true);
    }
    else {
        scoreBoard->updateScore(false);
    }
    std::cout << "Game ended!" << std::endl;
}