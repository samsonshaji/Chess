#include <iostream>
#include "controller.h"
#include "board.h"

Controller::Controller(Player* player1, Player* player2) : 
player1(player1), player2(player2), currentPlayer(player1), gameEnded(false) {}

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
    std::cout << "Game ended!" << std::endl;
}