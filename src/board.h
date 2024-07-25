#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"
#include "move.h"
#include "square.h"
#include "subject.h"
#include "colour.h"
#include "controller.h"

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
    Square* getSquare(int x, int y) const;
    void setController(Controller* ctrl);
    bool isMoveLegal(const Move& move) const;
private:
    std::vector<std::vector<Square*>> board;
    Controller* controller;
    void setupInitialBoard();
    Square* findKing(Colour colour) const;
    // Add other private helper functions as needed
};

#endif // BOARD_H
