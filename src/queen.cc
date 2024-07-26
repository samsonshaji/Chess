#include "queen.h"


Queen::Queen(Colour c) : Piece(c) {
    type = PieceType::Queen;
    symbol = (c == Colour::White) ? 'Q' : 'q';
}

//fill the vector with all possible Moves a queen can make at any given time
std::vector<Move> Queen::getValidMoves() const {
    std::vector<Move> validMoves;
    
    //check all squares to the right of the queen
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
    
    //check all squares to the left of the queen
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
    
    //check all squares above the queen
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
    
    //check all squares below the queen
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

    //check all squares to the top right of the queen
    for (int i = 1; square->getX() + i < 8 && square->getY() + i < 8; i++) {
        if (board->getSquare(square->getX() + i, square->getY() + i)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() + i, square->getY() + i), MoveType::Normal));
        } else if (board->getSquare(square->getX() + i, square->getY() + i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() + i, square->getY() + i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }

    //check all squares to the top left of the queen
    for (int i = 1; square->getX() - i >= 0 && square->getY() + i < 8; i++) {
        if (board->getSquare(square->getX() - i, square->getY() + i)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() - i, square->getY() + i), MoveType::Normal));
        } else if (board->getSquare(square->getX() - i, square->getY() + i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() - i, square->getY() + i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }

    //check all squares to the bottom right of the queen
    for (int i = 1; square->getX() + i < 8 && square->getY() - i >= 0; i++) {
        if (board->getSquare(square->getX() + i, square->getY() - i)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() + i, square->getY() - i), MoveType::Normal));
        } else if (board->getSquare(square->getX() + i, square->getY() - i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() + i, square->getY() - i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }

    //check all squares to the bottom left of the queen
    for (int i = 1; square->getX() - i >= 0 && square->getY() - i >= 0; i++) {
        if (board->getSquare(square->getX() - i, square->getY() - i)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() - i, square->getY() - i), MoveType::Normal));
        } else if (board->getSquare(square->getX() - i, square->getY() - i)->getPiece()->getColour() != colour) {
            validMoves.push_back(Move(square, board->getSquare(square->getX() - i, square->getY() - i), MoveType::Capture));
            break;
        } else {
            break;
        }
    }

    return validMoves;
}
