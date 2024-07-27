#include "rook.h"

using namespace std;

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::Rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

PieceType Rook::getPieceType() const {
    return PieceType::Rook;
}

void Rook::addStraightMoves(vector<Move>& moves, int xDir, int yDir) const {
    int x = square->getX() + xDir;
    int y = square->getY() + yDir;
    
    while (x >= 0 && x < 8 && y >= 0 && y < 8) {
        
        Square* targetSquare = board->getSquare(x, y);
        
        if (targetSquare->getPiece() == nullptr) {
            moves.push_back(Move(square, targetSquare, MoveType::Normal));
        } 
        else if (targetSquare->getPiece()->getColour() != colour) {
            if (targetSquare->getPiece()->getPieceType() == PieceType::King) {
                board->isInCheck(targetSquare->getPiece()->getColour());
            }
            moves.push_back(Move(square, targetSquare, MoveType::Capture));
            break;
        } else {
            break;
        }
        x += xDir;
        y += yDir;
    }
}

bool Rook::canCastle() const {
    return !hasMoved;
}

vector<Move> Rook::getValidMoves() const {
    vector<Move> moves;
    addStraightMoves(moves, 1, 0);
    addStraightMoves(moves, -1, 0);
    addStraightMoves(moves, 0, 1);
    addStraightMoves(moves, 0, -1);
    return moves;
}