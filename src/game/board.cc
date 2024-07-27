#include "board.h"
#include <iostream>
#include <algorithm>
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "colour.h"

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

void Board::clearBoard() {
    for (auto& row : board) {
        for (auto& square : row) {
            if (square->getPiece() != nullptr) {
                delete square->getPiece();
            }
            square->setPiece(nullptr);
        }
    }
}

void Board::setupInitialBoard() {
    clearBoard();

    // calls square's setPiece function
    // white pieces

    addPiece(new Rook(Colour::White), board[0][0]);
    addPiece(new Knight(Colour::White), board[0][1]);
    addPiece(new Bishop(Colour::White), board[0][2]);
    addPiece(new Queen(Colour::White), board[0][3]);
    addPiece(new King(Colour::White), board[0][4]);
    addPiece(new Bishop(Colour::White), board[0][5]);
    addPiece(new Knight(Colour::White), board[0][6]);
    addPiece(new Rook(Colour::White), board[0][7]);
    for (int i = 0; i < 8; i++) {
        addPiece(new Pawn(Colour::White), board[1][i]);
    }

    // black pieces
    addPiece(new Rook(Colour::Black), board[7][0]);
    addPiece(new Knight(Colour::Black), board[7][1]);
    addPiece(new Bishop(Colour::Black), board[7][2]);
    addPiece(new Queen(Colour::Black), board[7][3]);
    addPiece(new King(Colour::Black), board[7][4]);
    addPiece(new Bishop(Colour::Black), board[7][5]);
    addPiece(new Knight(Colour::Black), board[7][6]);
    addPiece(new Rook(Colour::Black), board[7][7]);
    for (int i = 0; i < 8; i++) {
        addPiece(new Pawn(Colour::Black), board[6][i]);
    }

    // empty squares
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j]->setPiece(nullptr);
        }
    }
}

void Board::addPiece(Piece* piece, Square* square) {
    square->setPiece(piece);
}

void Board::removePiece(Square* square) {
    if (square->getPiece() != nullptr) {
        delete square->getPiece();
    }
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
            if (piece && piece->getColour() == colour && piece->getPieceType() == PieceType::king) {
                return square;
            }
        }
    }
    // not found -- should never happen
    return nullptr;
}

void Board::addMoveToStack(const Move& move) {
    moveStack.push_back(move);
}

std::vector<Move> Board::getMoveStack() const {
    return moveStack;
}

Move Board::getLastMove() const {
    return moveStack.back();
}

bool Board::isMoveLegal(const Move& move) const {
    std::vector<Move> validMoves = move.getFrom()->getPiece()->getValidMoves();
    // check if move is in validMoves
    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
}



bool Board::movePiece(const Move& move) {
    if (!isMoveLegal(move)) {
        return false;
    }

    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();

    Move ourMove = move;

    // Handle castling
    if (piece->getPieceType() == PieceType::king && !(piece->getHasMoved())) {
        if (to->getX() == from->getX() + 2) {
            // Kingside castling
            Square* rookFrom = getSquare(7, from->getY());
            Square* rookTo = getSquare(5, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->setPiece(nullptr);
            rookTo->setPiece(rook);
            rook->setHasMoved(true);

            ourMove.setMoveType(MoveType::Castling);

        } else if (to->getX() == from->getX() - 2) {
            // Queenside castling
            Square* rookFrom = getSquare(0, from->getY());
            Square* rookTo = getSquare(3, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->setPiece(nullptr);
            rookTo->setPiece(rook);
            rook->setHasMoved(true);

            ourMove.setMoveType(MoveType::Castling);
        }
    }

    // Handle en passant
    if (piece->getPieceType() == PieceType::pawn &&
        from->getX() != to->getX() && to->getPiece() == nullptr) {
        Square* target = getSquare(to->getX(), from->getY());
        target->setPiece(nullptr);
        ourMove.setMoveType(MoveType::EnPassant);
    }

    // Set piece as moved
    if (piece->getPieceType() == PieceType::king ||
        piece->getPieceType() == PieceType::rook) {
        piece->setHasMoved(true);
    }
    if (piece->getPieceType() == PieceType::pawn &&
        abs(to->getY() - from->getY()) == 2) {
        // static_cast<Pawn*>(piece)->setDashed(true);
        piece->setHasMoved(true);
        ourMove.setMoveType(MoveType::DoublePawn);
    }

    to->setPiece(piece);
    from->setPiece(nullptr);

    // Handle promotion
    if (piece->getPieceType() == PieceType::pawn && (to->getY() == 0 || to->getY() == 7)) {
        PieceType promotionType = controller->getPromotedTo();

        Piece* promotedPiece = nullptr;
        switch (promotionType) {
            case PieceType::queen:
                promotedPiece = new Queen(piece->getColour());
                break;
            case PieceType::rook:
                promotedPiece = new Rook(piece->getColour());
                break;
            case PieceType::bishop:
                promotedPiece = new Bishop(piece->getColour());
                break;
            case PieceType::knight:
                promotedPiece = new Knight(piece->getColour());
                break;
            default:
                break;
        }
        ourMove.setMoveType(MoveType::Promotion);
        to->setPiece(promotedPiece);
        delete piece;
    }

    // Handle capture
    if (to->getPiece() != nullptr) {
        ourMove.setMoveType(MoveType::Capture);
        ourMove.setCapturedPiece(to->getPiece());
        delete to->getPiece();
    }

    addMoveToStack(ourMove);
    notifyObservers();

    // Reset the moved state for pawns of the opposite color
    Colour oppositeColor = (piece->getColour() == Colour::White) ? Colour::Black : Colour::White;
    for (auto& row : board) {
        for (auto& square : row) {
            Piece* p = square->getPiece();
            if (p && p->getColour() == oppositeColor && p->getPieceType() == PieceType::pawn) {
                // static_cast<Pawn*>(p)->setDashed(false);
                p->setHasMoved(false);
            }
        }
    }
    return true;
}

void Board::undoMove() {
    if (moveStack.empty()) {
        return;
    }

    Move lastMove = moveStack.back();
    Square* from = lastMove.getFrom();
    Square* to = lastMove.getTo();

    Piece* piece = to->getPiece();
    from->setPiece(piece);

    // Handle capture
    if (lastMove.getCapturedPiece() != nullptr) {
        to->setPiece(lastMove.getCapturedPiece());
    } else {
        to->setPiece(nullptr);
    }

    // Handle castling
    if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
        if (to->getX() == from->getX() + 2) {
            // Kingside castling
            Square* rookFrom = getSquare(5, from->getY());
            Square* rookTo = getSquare(7, from->getY());
            Piece* rook = rookTo->getPiece();
            rookTo->setPiece(nullptr);
            rookFrom->setPiece(rook);
        } else if (to->getX() == from->getX() - 2) {
            // Queenside castling
            Square* rookFrom = getSquare(3, from->getY());
            Square* rookTo = getSquare(0, from->getY());
            Piece* rook = rookTo->getPiece();
            rookTo->setPiece(nullptr);
            rookFrom->setPiece(rook);
        }
    }

    // Handle en passant
    if (piece->getPieceType() == PieceType::pawn &&
        from->getX() != to->getX() && to->getPiece() == nullptr) {
        Square* target = getSquare(to->getX(), from->getY());
        target->setPiece(new Pawn(piece->getColour()));
    }

    // Reset piece's moved state
    if (piece->getPieceType() == PieceType::king ||
        piece->getPieceType() == PieceType::rook) {
        piece->setHasMoved(false);
    }

    // Handle promotion
    if (piece->getPieceType() == PieceType::pawn && (to->getY() == 0 || to->getY() == 7)) {
        delete piece;
        to->setPiece(new Pawn(piece->getColour()));
    }

    moveStack.pop_back();
    notifyObservers();
}


bool Board::isInCheck(Colour colour) const {
    Square* kingSquare = findKing(colour);
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() != colour) {
                // if piece->canMoveTo() king.square
                std::vector <Move> validMoves = piece->getValidMoves();
                for (const auto& move : validMoves) {
                    if (move.getTo() == kingSquare) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Colour colour) const {
    if (!isInCheck(colour)) {
        return false;
    }

    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getValidMoves();
                for (const auto& move : validMoves) {
                    Board copy = getState();
                    copy.movePiece(move);
                    if (!copy.isInCheck(colour)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(Colour colour) const {
    if (isInCheck(colour)) {
        return false;
    }

    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getValidMoves();
                for (const auto& move : validMoves) {
                    Board copy = getState();
                    copy.movePiece(move);
                    if (!copy.isInCheck(colour)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
