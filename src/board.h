#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"
#include "move.h"
#include "square.h"
#include "colour.h"
#include "subject.h"

class Board : public Subject {
public:
    Board();
    void display() const;
    bool movePiece(const Move& move);
    bool isInCheck(Colour colour) const;
    bool isCheckmate(Colour colour) const;
    bool isStalemate(Colour colour) const;
    void resetBoard();
    Board getState() const override;
private:
    std::vector<std::vector<Square*>> board;
    void setupInitialBoard();
    bool isMoveLegal(const Move& move) const;
    // Add other private helper functions as needed
};

#endif // BOARD_H
