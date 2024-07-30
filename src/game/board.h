#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "move.h"
#include "square.h"
#include "colour.h"
#include "controller.h"
#include "piece.h"

class Controller;

class Board : public Subject {
private:
    std::vector<std::vector<Square*>> board;
    Controller* controller;
    std::vector<Move> moveStack;
public:
    Board();
    ~Board();
    Square* findKing(Colour colour) const;

    void setupInitialBoard();

    void setController(Controller* ctrl);
    Square* getSquare(int x, int y) const;

    std::vector<Move> getMoveStack() const;
    Move getLastMove() const;

    void addMoveToStack(const Move& move);
    void undoMove();

    void addPiece(Piece* piece, Square* square);
    void removePiece(Square* square);
    void clearBoard();

    bool isValidSetup() const;

    std::vector<std::vector<Square*>> getState() const override;

    bool movePiece(const Move& move);
    bool overrideMovePiece(const Move& move);
    

    bool isInCheck(Colour colour) const;
    bool isCheckmate(Colour colour);
    bool isStalemate(Colour colour) const;

    void print() const;

    bool isMoveLegal(const Move& move);
    std::vector<std::vector<Square*>> getBoard();

    MoveType determineMoveType(const Move& move);
};

#endif 
