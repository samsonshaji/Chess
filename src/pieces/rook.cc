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

vector<Move> Rook::getValidMoves() const {
    vector<Move> moves;
    addStraightMoves(moves, 1, 0);
    addStraightMoves(moves, -1, 0);
    addStraightMoves(moves, 0, 1);
    addStraightMoves(moves, 0, -1);

    // castling - king side
    if (board->canCastle(colour, true)) {
        if (colour == Colour::White) {
            if (board->getSquare(5, 0)->getPiece() == nullptr &&
                board->getSquare(6, 0)->getPiece() == nullptr) {
                moves.push_back(Move(square, board->getSquare(6, 0), MoveType::Castle));
            }
        } else {
            if (board->getSquare(5, 7)->getPiece() == nullptr &&
                board->getSquare(6, 7)->getPiece() == nullptr) {
                moves.push_back(Move(square, board->getSquare(6, 7), MoveType::Castle));
            }
        }
    }

    // castling - queen side
    if (board->canCastle(colour, false)) {
        if (colour == Colour::White) {
            if (board->getSquare(1, 0)->getPiece() == nullptr &&
                board->getSquare(2, 0)->getPiece() == nullptr &&
                board->getSquare(3, 0)->getPiece() == nullptr) {
                moves.push_back(Move(square, board->getSquare(2, 0), MoveType::Castle));
            }
        } else {
            if (board->getSquare(1, 7)->getPiece() == nullptr &&
                board->getSquare(2, 7)->getPiece() == nullptr &&
                board->getSquare(3, 7)->getPiece() == nullptr) {
                moves.push_back(Move(square, board->getSquare(2, 7), MoveType::Castle));
            }
        }
    }

    return moves;
}