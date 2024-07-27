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
private:
    std::vector<std::vector<Square*>> board;
    Controller* controller;
    void setupInitialBoard();
    void clearBoard();
    void addPiece(Piece* piece, Square* square);
    void removePiece(Square* square);
    vector<Move> moveStack;
public:
    Board();
    ~Board();
    Square* findKing(Colour colour) const;

    void setController(Controller* ctrl);
    Square* getSquare(int x, int y) const;

    vector<Move> getMoveStack() const;
    void addMoveToStack(const Move& move);
    void undoMove();

    Board getState() const;

    // TODO all of these
    // false if move is illegal, true + updates board otherwise
    bool movePiece(const Move& move);
    bool isInCheck(Colour colour) const;
    bool isCheckmate(Colour colour) const;
    bool isStalemate(Colour colour) const;

    bool isMoveLegal(const Move& move) const;
};

#endif // BOARD_H
