#include "bishop.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Bishop::Bishop(Colour c) : Piece(c) {
    type = PieceType::bishop;
    symbol = (c == Colour::White) ? 'B' : 'b';
}

PieceType Bishop::getPieceType() const {
    return PieceType::bishop;
}

void Bishop::addDiagonalMoves(vector<Move>& moves, int xDir, int yDir) const {
    int x = square->getX() + xDir;
    int y = square->getY() + yDir;
    
    while (x >= 0 && x < 8 && y >= 0 && y < 8) {
        
        Square* targetSquare = board->getSquare(x, y);
        
        if (targetSquare->getPiece() == nullptr) {
            moves.push_back(Move(square, targetSquare, MoveType::Normal));
        } 
        else if (targetSquare->getPiece()->getColour() != colour) {
            if (targetSquare->getPiece()->getPieceType() == PieceType::king) {
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

vector<Move> Bishop::getValidMoves() const {
    vector<Move> moves;
    addDiagonalMoves(moves, 1, 1);
    addDiagonalMoves(moves, 1, -1);
    addDiagonalMoves(moves, -1, 1);
    addDiagonalMoves(moves, -1, -1);
    return moves;
}

