#include "piece.h"
#include "square.h"
#include "board.h"
#include <vector>

using namespace std;

Piece::~Piece() {
    square = nullptr;
    board = nullptr;
}

PieceType Piece::getPieceType() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

Piece::Piece(Colour c) : colour(c) {}

Square *Piece::getSquare() const {
    return (square) ? square : nullptr;
}

void Piece::setSquare(Square *s) {
    square = s;
}

void Piece::setBoard(Board *b) {
    board = b;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool m) {
    hasMoved = m;
}

char Piece::getSymbol() const {
    return symbol;
}

bool Piece::operator==(const Piece &other) const {
    return type == other.type && square->getX() == other.square->getX() && square->getY() == other.square->getY();
}

void Piece::addDirectionalMoves(vector<Move>& moves, int xDir, int yDir) const {
    int x = square->getX() + xDir;
    int y = square->getY() + yDir;
    
    while (x >= 0 && x < 8 && y >= 0 && y < 8) {
        
        Square* targetSquare = board->getSquare(x, y);

        Move m = Move(square, targetSquare);
        
        if (targetSquare->getPiece() == nullptr) {
            m.setMoveType(MoveType::Normal);
            moves.push_back(m);
        } 
        else if (targetSquare->getPiece()->getColour() != colour) {
            m.setMoveType(MoveType::Capture);
            moves.push_back(m);
            break;
        } else {
            break;
        }
        x += xDir;
        y += yDir;
    }
}

bool Piece::getEnPassantable() const {
    return enPassantable;
}

void Piece::setEnPassantable(bool e) {
    enPassantable = e;
}