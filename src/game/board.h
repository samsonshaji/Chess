#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "move.h"
#include "square.h"
#include "subject.h"
#include "colour.h"
#include "controller.h"
#include "piece.h"

class Board : public Subject {
private:
    std::vector<std::vector<Square*>> board;
    Controller* controller;
    void setupInitialBoard();
    std::vector<Move> moveStack;
public:
    Board();
    ~Board();
    Square* findKing(Colour colour) const;

    void setController(Controller* ctrl);
    Square* getSquare(int x, int y) const;

    std::vector<Move> getMoveStack() const;
    Move getLastMove() const;
    
    void addMoveToStack(const Move& move);
    void undoMove();

    void addPiece(Piece* piece, Square* square);
    void removePiece(Square* square);
    void clearBoard();

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


// TODO:
// movePiece (+ determine move type)
// undo move
// in check, stale, checkmate