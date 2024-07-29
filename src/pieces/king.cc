#include "king.h"
#include "board.h"
#include "move.h"
#include "square.h"

King::King(Colour c) : Piece(c) {
    type = PieceType::king;
    symbol = (c == Colour::White) ? 'K' : 'k';
}

bool King::isKingMoveValid(const Move& move, const Board& board) const {
    // Calculate the difference in x and y coordinates
    int deltaX = abs(move.getFrom()->getX() - move.getTo()->getX());
    int deltaY = abs(move.getFrom()->getY() - move.getTo()->getY());

    // The King can move one square in any direction
    if (deltaX <= 1 && deltaY <= 1) {
        // Ensure the move does not put the King in check
        return !(board.isMoveLegal(move));
    }
    return false;
}

std::vector<Move> King::getValidMoves() const {
    std::vector<Move> validMoves;

    if (!square || !board) return validMoves;

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
                    if (targetSquare->getPiece() == nullptr) {
                        validMoves.push_back(Move(square, targetSquare, MoveType::Normal));
                    } else if (targetSquare->getPiece()->getColour() != colour) {
                        if (targetSquare->getPiece()->getPieceType() == PieceType::king) {
                            board->isInCheck(targetSquare->getPiece()->getColour());
                        }
                        validMoves.push_back(Move(square, targetSquare, MoveType::Capture));
                    }
                }
            }
        }
    }

    // Castling logic
    if (!hasMoved) {
        // Check for kingside castling

        bool kingside_1, kingside_2, kingside_3, kingside_4 = false;

        if (board->getSquare(curX + 1, curY) != nullptr) {
            kingside_1 = board->getSquare(curX + 1, curY)->getPiece() == nullptr;
        }
        if (board->getSquare(curX + 2, curY) != nullptr) {
            kingside_2 = board->getSquare(curX + 2, curY)->getPiece() == nullptr;
        }
        if (board->getSquare(curX + 3, curY) != nullptr) {
            kingside_3 = board->getSquare(curX + 3, curY)->getPiece() != nullptr;
        }
        if (board->getSquare(curX + 3, curY) != nullptr) {
            if (board->getSquare(curX + 3, curY)->getPiece() != nullptr) {
                kingside_4 = board->getSquare(curX + 3, curY)->getPiece()->getPieceType() == PieceType::rook;
            }
        }

        if (kingside_1 && kingside_2 && kingside_3 && kingside_4) {
            // Additional checks to ensure the King is not in check, doesn't move through check, and doesn't end in check
            if (!board->isInCheck(colour) &&
                isKingMoveValid(Move(square, board->getSquare(curX + 1, curY)), *board) &&
                isKingMoveValid(Move(square, board->getSquare(curX + 2, curY)), *board)) {
                validMoves.push_back(Move(square, board->getSquare(curX + 2, curY), MoveType::Castling));
            }
        }

        bool queenside_1, queenside_2, queenside_3, queenside_4, queenside_5 = false;
        if (board->getSquare(curX - 1, curY) != nullptr) {
            queenside_1 = board->getSquare(curX - 1, curY)->getPiece() == nullptr;
        }

        if (board->getSquare(curX - 2, curY) != nullptr) {
            queenside_2 = board->getSquare(curX - 2, curY)->getPiece() == nullptr;
        }

        if (board->getSquare(curX - 3, curY) != nullptr) {
            queenside_3 = board->getSquare(curX - 3, curY)->getPiece() == nullptr;
        }

        if (board->getSquare(curX - 4, curY) != nullptr) {
            queenside_4 = board->getSquare(curX - 4, curY)->getPiece() != nullptr;
        }

        if (board->getSquare(curX - 4, curY) != nullptr) {
            if (board->getSquare(curX - 4, curY)->getPiece() != nullptr) {
                queenside_5 = board->getSquare(curX - 4, curY)->getPiece()->getPieceType() == PieceType::rook;
            }
        }

        if (queenside_1 && queenside_2 && queenside_3 && queenside_4 && queenside_5) {
            // Additional checks to ensure the King is not in check, doesn't move through check, and doesn't end in check
            if (!board->isInCheck(colour) &&
                isKingMoveValid(Move(square, board->getSquare(curX - 1, curY)), *board) &&
                isKingMoveValid(Move(square, board->getSquare(curX - 2, curY)), *board)) {
                validMoves.push_back(Move(square, board->getSquare(curX - 2, curY), MoveType::Castling));
            }
        }
    }
    return validMoves;
}



