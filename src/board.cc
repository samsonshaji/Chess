#include "board.h"

Board::Board() {
    for (int i = 0; i < 8; i++) {
        std::vector<Square> row;
        for (int j = 0; j < 8; j++) {
            row.push_back(Square());
        }
        board.push_back(row);
    }
}


void Board::notify() {
    printBoard();
}

// TODO
void Board::move(Move m) {
    board[m.to.row][m.to.col].setPiece(board[m.from.row][m.from.col].getPiece());
    board[m.from.row][m.from.col].setPiece(PieceType::Pawn);
}

void Board::printBoard() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << std::setw(2) << board[i][j].getPiece() << " ";
        }
        std::cout << std::endl;
    }
}

void Board::isCheck(Color c) {
    // TODO
}

void Board::isCheckmate(Color c) {
    // TODO
}

void Board::isStalemate(Color c) {
    // TODO
}

PieceType Board::getPieceType(int row, int col) const {
    return board[row][col].getPiece();
}