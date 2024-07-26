#include "knight.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Knight::Knight(Colour c) : Piece(c) {
    type = PieceType::Knight;
    symbol = (c == Colour::White) ? 'N' : 'n';
}

//fill the vector with all possible Moves a knight can make at any given time
vector<Move> Knight::getValidMoves() const {
    vector<Move> validMoves;
    
    int x = square->getX();
    int y = square->getY();

    int jumpx;
    int jumpy;

    if (y + 2 < 8) {
        jumpy = y + 2;
        if (x + 1 < 8) {
            jumpx = x + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
        if (x - 1 >= 0) {
            jumpx = x - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
    }

    if (y - 2 >= 0) {
        jumpy = y - 2;
        if (x + 1 < 8) {
            jumpx = x + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
        if (x - 1 >= 0) {
            jumpx = x - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
    }

    if (x + 2 < 8) {
        jumpx = x + 2;
        if (y + 1 < 8) {
            jumpy = y + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
        if (y - 1 >= 0) {
            jumpy = y - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
    }

    if (x - 2 >= 0) {
        jumpx = x - 2;
        if (y + 1 < 8) {
            jumpy = y + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
        if (y - 1 >= 0) {
            jumpy = y - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            if (jump->getPiece() == nullptr) {
                validMoves.push_back(Move(square, jump, MoveType::Normal));
            }
            else if (jump->getPiece()->getColour() != colour) {
                validMoves.push_back(Move(square, jump, MoveType::Capture));
            }
        }
    }
    
    return validMoves;
}