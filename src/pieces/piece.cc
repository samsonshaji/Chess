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

void Piece::addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const {
    int curX = square->getX();
    int curY = square->getY();
    int posX = curX + xDir;
    int posY = curY + yDir;

    while(posX >= 0 && posX < 8 && posY >= 0 && posY < 8){
        if (board->getSquare(posX, posY) && board->getSquare(posX, posY)->getPiece() != nullptr) {
            if (board->getSquare(posX, posY)->getPiece()->getColour() != colour) {
                moves.push_back(Move(square, board->getSquare(posX, posY), MoveType::Capture));
            }
            break;
        }
        moves.push_back(Move(square, board->getSquare(posX, posY), MoveType::Normal));
        posX+=xDir;
        posY+=yDir;
    }
}
