#include "king.h"
#include "board.h"
#include "move.h"
#include "square.h"

King::King(Colour c) : Piece(c) {
    type = PieceType::king;
    symbol = (c == Colour::White) ? 'K' : 'k';
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


    // Castling logic - Kingside
    if (!(hasMoved) && 
        board->getSquare(5,curY)->getPiece() == nullptr &&
        board->getSquare(6,curY)->getPiece() == nullptr &&
        board->getSquare(7,curY)->getPiece() != nullptr)
    {
        // std::cout << std::endl;
        // std::cout << "Checking kingside castling for colour: " 
        //           << (colour == Colour::White ? "White" : "Black") 
        //           << std::endl;

        if (!(board->getSquare(7, curY)->getPiece()->getHasMoved())) {
            // 4 -> king
            // 5 -> empty
            // 6 -> empty
            // 7 -> rook

            // make sure if king moves to 5 -- not in check
            // std::cout << "Rook has not moved" << std::endl;

            Move tempMove(square, board->getSquare(5,curY), MoveType::Normal);
            bool valid = board->overrideMovePiece(tempMove);
            bool isCheck5 = board->isInCheck(colour);

            // std::cout << std::endl;
            // std::cout << "-----------------" << std::endl;
            // board->print();
            // std::cout << "-----------------" << std::endl;
            // std::cout << std::endl;


            if (!isCheck5) {
                // make sure if king moves to 6 -- not in check
                Move tempMove2(board->getSquare(5,curY), board->getSquare(6,curY), MoveType::Normal);
                bool valid2 = board->overrideMovePiece(tempMove2);
                bool isCheck6 = board->isInCheck(colour);

                // std::cout << std::endl;
                // std::cout << "-----------------" << std::endl;
                // board->print();
                // std::cout << "-----------------" << std::endl;
                // std::cout << std::endl;

                if (!isCheck6) {
                    // std::cout << "Castling move pushed" << std::endl;
                    // std::cout << board->getSquare(4,curY)->getX() << " " << board->getSquare(4,curY)->getY() << std::endl;
                    // std::cout << board->getSquare(7,curY)->getX() << " " << board->getSquare(7,curY)->getY() << std::endl;
                    validMoves.push_back(Move(board->getSquare(4,curY), board->getSquare(6,curY), MoveType::Castling));
                }
                board->undoMove();
            }
            board->undoMove();

            
        }

        // we're good here
        // std::cout << std::endl;
        // std::cout << "-----after undoMove-----" << std::endl;
        // board->print();
        // std::cout << "-------------------------" << std::endl;
        // std::cout << std::endl;

    }

    // Castling logic - Queenside
    if (!(hasMoved) && 
        board->getSquare(3,curY)->getPiece() == nullptr &&
        board->getSquare(2,curY)->getPiece() == nullptr &&
        board->getSquare(1,curY)->getPiece() == nullptr &&
        board->getSquare(0,curY)->getPiece() != nullptr)
    {
        if (!(board->getSquare(0, curY)->getPiece()->getHasMoved())) {
            // 0 -> rook
            // 1 -> empty
            // 2 -> empty
            // 3 -> empty
            // 4 -> king

            // make sure if king moves to 3 -- not in check
            // std::cout << "Rook has not moved" << std::endl;

            Move tempMove(board->getSquare(4,curY), board->getSquare(3,curY), MoveType::Normal);
            bool valid = board->overrideMovePiece(tempMove);
            bool isCheck3 = board->isInCheck(colour);

            if (!isCheck3) {
                // make sure if king moves to 2 -- not in check
                Move tempMove2(board->getSquare(3,curY), board->getSquare(2,curY), MoveType::Normal);
                bool valid2 = board->overrideMovePiece(tempMove2);
                bool isCheck2 = board->isInCheck(colour);

                if (!isCheck2) {
                    // make sure if king moves to 1 -- not in check
                    Move tempMove3(board->getSquare(2,curY), board->getSquare(1,curY), MoveType::Normal);
                    bool valid3 = board->overrideMovePiece(tempMove3);
                    bool isCheck1 = board->isInCheck(colour);

                    if (!isCheck1) {
                        // std::cout << "Castling move pushed" << std::endl;
                        validMoves.push_back(Move(board->getSquare(4,curY), board->getSquare(2,curY), MoveType::Castling));
                    }
                    board->undoMove();
                }
                board->undoMove();
            }
            board->undoMove();
        }
    }
    return validMoves;
}



