#include "knight.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Knight::Knight(Colour c) : Piece(c) {
    type = PieceType::knight;
    symbol = (c == Colour::White) ? 'N' : 'n';
}

//fill the vector with all possible Moves a knight can make at any given time
vector<Move> Knight::getAllMoves() const {
    vector<Move> validMoves;

    if(!square) return validMoves;
    
    //current position of the knight
    int x = square->getX();
    int y = square->getY();

    //8 total moves a knight can make

    //check bounds for each move to make sure it is within the board
    if (y + 2 < 8) {
        int jumpy = y + 2;
        //check bounds for each move to make sure it is within the board
        if (x + 1 < 8) {
            int jumpx = x + 1;
            //get the square at the destination position
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            //if the square is empty, add a normal move to the vector
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            //if the square is occupied by an enemy piece, add a capture move to the vector
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
        //check bounds for each move to make sure it is within the board
        if (x - 1 >= 0) {
            int jumpx = x - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
    }

    if (y - 2 >= 0) {
        int jumpy = y - 2;
        if (x + 1 < 8) {
            int jumpx = x + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
        if (x - 1 >= 0) {
            int jumpx = x - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
    }

    if (x + 2 < 8) {
        int jumpx = x + 2;
        if (y + 1 < 8) {
            int jumpy = y + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
        if (y - 1 >= 0) {
            int jumpy = y - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
    }

    if (x - 2 >= 0) {
        int jumpx = x - 2;
        if (y + 1 < 8) {
            int jumpy = y + 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
        if (y - 1 >= 0) {
            int jumpy = y - 1;
            Square* jump = board->getSquare(jumpx, jumpy);
            Move m = Move(square, jump);
            if (jump->getPiece() == nullptr) {
                m.setMoveType(MoveType::Normal);
            }
            else if (jump->getPiece()->getColour() != colour) {
                m.setMoveType(MoveType::Capture);
            }
            validMoves.push_back(m);
        }
    }
    
    return validMoves;
}