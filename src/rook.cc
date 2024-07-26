#include "rook.h"

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::Rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

//fill the vector with all possible Moves a rook can make at any given time
std::vector<Move> Rook::getValidMoves() const {
    std::vector<Move> validMoves;
    
    //check all squares to the right of the rook
    for (int i = square->getX() + 1; i < 8; i++) {
        if (board->getSquare(i, square->getY())->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(i, square->getY()), MoveType::Normal));
        } else if (board->getSquare(i, square->getY())->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(i, square->getY()), MoveType::Capture));
            break;
        } else {
            break;
        }
    }
    
    //check all squares to the left of the rook
    for (int i = square->getX() - 1; i >= 0; i--) {
        if (board->getSquare(i, square->getY())->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(i, square->getY()), MoveType::Normal));
        } else if (board->getSquare(i, square->getY())->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(i, square->getY()), MoveType::Capture));
            break;
        } else {
            break;
        }
    }
    
    //check all squares above the rook
    for (int i = square->getY() + 1; i < 8; i++) {
        if (board->getSquare(square->getX(), i)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX(), i), MoveType::Normal));
        } else if (board->getSquare(square->getX(), i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX(), i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }
    
    //check all squares below the rook
    for (int i = square->getY() - 1; i >= 0; i--) {
        if (board->getSquare(square->getX(), i)->getPiece () == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX(), i), MoveType::Normal));
        } else if (board->getSquare(square->getX(), i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX(), i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }

    return validMoves;
}