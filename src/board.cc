#include "board.h"
#include <iostream>

Board::Board() {
    setupInitialBoard();
}

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

// bool Board::movePiece(const Move& move) {
//     if (!isMoveLegal(move)) return false;
//     Square* fromSquare = board[move.from.getX()][move.from.getY()];
//     Square* toSquare = board[move.to.getX()][move.to.getY()];

//     toSquare->setPiece(fromSquare->getPiece());
//     fromSquare->setPiece(nullptr);
//     notifyObservers();
//     return true;
// }

// bool Board::isInCheck(Colour colour) const {
//     Square* kingSquare = findKing(colour);
//     for (const auto& row : board) {
//         for (const auto& square : row) {
//             Piece* piece = square->getPiece();
//             if (piece && piece->getColour() != colour) {
//                 // if (piece->canMoveTo(kingSquare->getX(), kingSquare->getY(), *this)) {
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }

bool Board::isCheckmate(Colour colour) const {
    if (!isInCheck(colour)) return false;
    // Additional logic to determine if any move can save the king from checkmate
    return false;
}

bool Board::isStalemate(Colour colour) const {
    if (isInCheck(colour)) return false;
    // Additional logic to determine if no legal moves are available
    return false;
}

void Board::resetBoard() {
    // Implement board reset logic
    setupInitialBoard();
    notifyObservers();
}

void Board::setupInitialBoard() {
    board.resize(8, std::vector<Square*>(8, nullptr));
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            board[x][y] = new Square(x, y);
            board[x][y]->setBoard(this);
        }
    }
    // Setup initial pieces (Pawns, Rooks, Knights, Bishops, Queens, Kings)
    // Place black pieces
    for (int y = 0; y < 8; ++y) {
        board[1][y]->setPiece(new Pawn(Black));
    }
    board[0][0]->setPiece(new Rook(Black));
    board[0][1]->setPiece(new Knight(Black));
    board[0][2]->setPiece(new Bishop(Black));
    board[0][3]->setPiece(new Queen(Black));
    board[0][4]->setPiece(new King(Black));
    board[0][5]->setPiece(new Bishop(Black));
    board[0][6]->setPiece(new Knight(Black));
    board[0][7]->setPiece(new Rook(Black));

    // Place white pieces
    for (int y = 0; y < 8; ++y) {
        board[6][y]->setPiece(new Pawn(White));
    }
    board[7][0]->setPiece(new Rook(White));
    board[7][1]->setPiece(new Knight(White));
    board[7][2]->setPiece(new Bishop(White));
    board[7][3]->setPiece(new Queen(White));
    board[7][4]->setPiece(new King(White));
    board[7][5]->setPiece(new Bishop(White));
    board[7][6]->setPiece(new Knight(White));
    board[7][7]->setPiece(new Rook(White));

    notifyObservers();
}

bool Board::isMoveLegal(const Move& move) const {
    // Implement move legality check
    return true;
}

Board Board::getState() const {
    return *this;
}

Square* Board::getSquare(int x, int y) const {
    return board[x][y];
}

void Board::setController(Controller* ctrl) {
    controller = ctrl;
}

Square* Board::findKing(Colour colour) const {
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour && piece->getPieceType() == King) {
                return square;
            }
        }
    }
    return nullptr; // Return nullptr if king is not found
}
