#include "robotLevelOne.h"
#include "move.h"

LevelOne::LevelOne() {}

Move LevelOne::makeMove(const Board& board) {
    Move move(nullptr, nullptr);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Square *from = board.getSquare(i, j);
            if (from->getPiece() && from->getPiece()->getColour() == Colour::White) {
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        Square *to = board.getSquare(k, l);

                        std::vector<Move> validMoves = from->getPiece()->getValidMoves();
                        for (Move m : validMoves) {
                            if (m.getTo() == to) {
                                move = m;
                                return move;
                            }
                        }
                    }
                }
            }
        }
    }
    return move;
}