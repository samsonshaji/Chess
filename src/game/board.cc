#include "board.h"
#include <iostream>

Board::Board() {
    setupInitialBoard();
}

Board::~Board() {
    for (auto& row : board) {
        for (auto& square : row) {
            delete square;
        }
    }
}

Board::clearBoard() {
    for (auto& row : board) {
        for (auto& square : row) {
            square->setPiece(nullptr);
        }
    }
}

void Board::setupInitialBoard() {
    clearBoard();

    // calls square's setPiece function
    for (int i = 0; i < 8; i++) {
        board[1][i]->setPiece(new Pawn(Colour::White));
        board[6][i]->setPiece(new Pawn(Colour::Black));
    }

    board[0][0]->setPiece(new Rook(Colour::White));
    board[0][1]->setPiece(new Knight(Colour::White));
    board[0][2]->setPiece(new Bishop(Colour::White));
    board[0][3]->setPiece(new Queen(Colour::White));
    board[0][4]->setPiece(new King(Colour::White));
    board[0][5]->setPiece(new Bishop(Colour::White));
    board[0][6]->setPiece(new Knight(Colour::White));
    board[0][7]->setPiece(new Rook(Colour::White));

    board[7][0]->setPiece(new Rook(Colour::Black));
    board[7][1]->setPiece(new Knight(Colour::Black));
    board[7][2]->setPiece(new Bishop(Colour::Black));
    board[7][3]->setPiece(new Queen(Colour::Black));
    board[7][4]->setPiece(new King(Colour::Black));
    board[7][5]->setPiece(new Bishop(Colour::Black));
    board[7][6]->setPiece(new Knight(Colour::Black));
    board[7][7]->setPiece(new Rook(Colour::Black));
}

void Board::addPiece(Piece* piece, Square* square) {
    square->setPiece(piece);
}

void Board::removePiece(Square* square) {
    square->setPiece(nullptr);
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
            if (piece && piece->getColour() == colour && piece->getPieceType() == PieceType::King) {
                return square;
            }
        }
    }
    // not found
    return nullptr;
}

void Board::addMoveToStack(const Move& move) {
    moveStack.push_back(move);
}

bool Board::isMoveLegal(const Move& move) const {
    // bishop
    if (move.getPiece()->getPieceType() == PieceType::Bishop) {

    }
}

bool Board::movePiece(const Move& move) {
    if (!isMoveLegal(move)) {
        return false;
    }

    Square* from = move.getFrom();
    Square* to = move.getTo();

    // check if capture, castling, etc...
    // need to get valid moves and everything...
    // TODO

    // move piece
    Piece* piece = from->getPiece();
    to->setPiece(piece);
    from->setPiece(nullptr);

    // add move to stack
    addMoveToStack(move);

    // notify controller
    // controller->notifyMove(move);

    return true;
}

bool Board::isInCheck(Colour colour) const {
    // TODO
    return false;
}

bool Board::isCheckmate(Colour colour) const {
    // TODO
    return false;
}

bool Board::isStalemate(Colour colour) const {
    // TODO
    return false;
}

vector<Move> getMoveStack() const {
    return moveStack;
}

void Board::undoMove() {
    if (moveStack.empty()) {
        return;
    }

    Move move = moveStack.back();
    moveStack.pop_back();

    Square* from = move.getFrom();
    Square* to = move.getTo();

    // move piece back
    Piece* piece = to->getPiece();
    from->setPiece(piece);

    // can't assume nullptr, could be a capture... TODO
    to->setPiece(nullptr);

    // notify controller somehow... TODO
    // controller->notifyUndoMove(move);
}