#include "king.h"
#include "board.h"
#include "move.h"
#include "square.h"

King::King(Colour c) : Piece(c) {
    type = PieceType::king;
    symbol = (c == Colour::White) ? 'K' : 'k';
}

std::vector<Move> King::getAllMoves() const {
    std::vector<Move> validMoves;

    if (!square) return validMoves;

    int curX = square->getX();
    int curY = square->getY();

    // Check all 8 possible directions for the King
    for (int deltaX = -1; deltaX <= 1; deltaX++) {
        for (int deltaY = -1; deltaY <= 1; deltaY++) {
            // Skip the current position
            if (deltaX != 0 || deltaY != 0) {
                int newX = curX + deltaX;
                int newY = curY + deltaY;

                // Ensure new position is within board limits
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                    Square *targetSquare = board->getSquare(newX, newY);

                    // Check if the target square is either empty or contains an opponent's piece
                    Move m = Move(square, targetSquare);
                    if (targetSquare->getPiece() == nullptr) {
                        m.setMoveType(MoveType::Normal);
                        validMoves.push_back(m);
                    } else if (targetSquare->getPiece()->getColour() != colour) {
                        m.setMoveType(MoveType::Capture);
                        validMoves.push_back(m);
                    }
                }
            }
        }
    }

    // Castling logic
    if (!getHasMoved()){
        if(board->getSquare(5, curY)->getPiece() == nullptr && board->getSquare(6, curY)->getPiece() == nullptr){
            if(board->getSquare(7, curY)->getPiece()->getPieceType() == PieceType::rook && !board->getSquare(7, curY)->getPiece()->getHasMoved()){
                if(board->getSquare(7, curY)->getPiece()->getColour() == colour){
                    Move m = Move(square, board->getSquare(6, curY));
                    m.setMoveType(MoveType::Castling);
                    validMoves.push_back(m);
                }
            }
        }

        if(board->getSquare(3, curY)->getPiece() == nullptr && board->getSquare(2, curY)->getPiece() == nullptr && board->getSquare(1, curY)->getPiece() == nullptr){
            if(board->getSquare(0, curY)->getPiece()->getPieceType() == PieceType::rook && !board->getSquare(0, curY)->getPiece()->getHasMoved()){
                if(board->getSquare(0, curY)->getPiece()->getColour() == colour){
                    Move m = Move(square, board->getSquare(2, curY));
                    m.setMoveType(MoveType::Castling);
                    validMoves.push_back(m);
                }
            }
        }
    }
    return validMoves;
}



