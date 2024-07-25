#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"
#include "move.h"

class Board {
public:
    Board();
    void display() const;
    bool movePiece(const Move& move);
    bool isInCheck(bool isWhite) const;
    bool isCheckmate(bool isWhite) const;
    bool isStalemate(bool isWhite) const;
    void resetBoard();
private:
    std::vector<std::vector<Piece*>> board;
    void setupInitialBoard();
    bool isMoveLegal(const Move& move) const;
    // Add other private helper functions as needed
};

#endif // BOARD_H
