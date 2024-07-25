#include "board.h"
#include <iostream>

Board::Board() {
    setupInitialBoard();
}

// leave to textObserver
void Board::display() const {
    for (const auto& row : board) {
        for (const auto& square : row) {
            if (square->getPiece()) {
                std::cout << square->getPiece()->getSymbol() << ' ';
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::movePiece(const Move& move) {
    if (!isMoveLegal(move)) return false;
    Square* fromSquare = board[move.from.x][move.from.y];
    Square* toSquare = board[move.to.x][move.to.y];

    toSquare->setPiece(fromSquare->getPiece());
    fromSquare->setPiece(nullptr);
    notifyObservers();
    return true;
}

bool Board::isInCheck(Colour colour) const {
    // Implement check detection logic
    return false;
}

bool Board::isCheckmate(Colour colour) const {
    // Implement checkmate detection logic
    return false;
}

bool Board::isStalemate(Colour colour) const {
    // Implement stalemate detection logic
    return false;
}

void Board::resetBoard() {
    // Implement board reset logic
    notifyObservers();
}

void Board::setupInitialBoard() {
    board.resize(8, std::vector<Square*>(8, nullptr));
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board[x][y] = new Square(x, y);
        }
    }
    // Place pieces on the board in the initial positions
    notifyObservers();
}

bool Board::isMoveLegal(const Move& move) const {
    // Implement move legality check
    return true;
}

// for now
Board Board::getState() const {
    return *this;
}

Square* Board::getSquare(int x, int y) const {
    return board[x][y];
}
