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

//check if the rook can castle, assumes king has not moved
bool Rook::canCastle() const {
    if (this->getHasMoved()) {
        return false;
    } 
    else {
        // check for both black and white rooks, both sides, king side - queen side castling

        // white rook
        if (colour == Colour::White) {
            // left rook
            if (square->getX() == 0) {
                if (board->getSquare(1, 0)->getPiece() == nullptr && board->getSquare(2, 0)->getPiece() == nullptr && board->getSquare(3, 0)->getPiece() == nullptr) {
                    if (board->getSquare(0, 0)->getPiece() != nullptr && board->getSquare(0, 0)->getPiece()->getHasMoved() == false) {
                        return true;
                    }
                }
            }

            // right rook
            else if (square->getX() == 7) {
                if (board->getSquare(5, 0)->getPiece() == nullptr && board->getSquare(6, 0)->getPiece() == nullptr) {
                    if (board->getSquare(7, 0)->getPiece() != nullptr && board->getSquare(7, 0)->getPiece()->getHasMoved() == false) {
                        return true;
                    }
                }
            }
        } 

        // black rook
        else {
            // left rook
            if (square->getX() == 0) {
                if (board->getSquare(1, 7)->getPiece() == nullptr && board->getSquare(2, 7)->getPiece() == nullptr && board->getSquare(3, 7)->getPiece() == nullptr) {
                    if (board->getSquare(0, 7)->getPiece() != nullptr && board->getSquare(0, 7)->getPiece()->getHasMoved() == false) {
                        return true;
                    }
                }
            } 

            // right rook
            else if (square->getX() == 7) {
                if (board->getSquare(5, 7)->getPiece() == nullptr && board->getSquare(6, 7)->getPiece() == nullptr) {
                    if (board->getSquare(7, 7)->getPiece() != nullptr && board->getSquare(7, 7)->getPiece()->getHasMoved() == false) {
                        return true;
                    }
                }
            }
        }
    }
}
