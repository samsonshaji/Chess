#include "queen.h"


Queen::Queen(Colour c) : Piece(c) {
    type = PieceType::Queen;
    symbol = (c == Colour::White) ? 'Q' : 'q';
}

PieceType Queen::getPieceType() const {
    return PieceType::Queen;
}

void Queen::addDiagonalMoves(std::vector<Move>& moves, int xDir, int yDir) const {
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

void Queen::addStraightMoves(std::vector<Move>& moves, int xDir, int yDir) const {
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

std::vector<Move> Queen::getValidMoves() const {
    std::vector<Move> moves;
    addDiagonalMoves(moves, 1, 1);
    addDiagonalMoves(moves, 1, -1);
    addDiagonalMoves(moves, -1, 1);
    addDiagonalMoves(moves, -1, -1);
    addStraightMoves(moves, 1, 0);
    addStraightMoves(moves, -1, 0);
    addStraightMoves(moves, 0, 1);
    addStraightMoves(moves, 0, -1);
    return moves;
}