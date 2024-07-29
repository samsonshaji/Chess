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
    void setupInitialBoard();
    std::vector<Piece*> blackPieces;
    std::vector<Piece*> whitePieces;
public:
    Board();
    ~Board();
    Square* findKing(Colour colour) const;

    void setController(Controller* ctrl);
    Square* getSquare(int x, int y) const;

    std::vector<Piece*> getBlackPieces() const;
    std::vector<Piece*> getWhitePieces() const;

    void removePiece(Square* square);
    void clearBoard();

    bool isValidSetup() const;

    virtual std::vector<std::vector<Square*>> getState() const override;

    // false if move is illegal, true + updates board otherwise
    bool movePiece(const Move& move, bool test = false);
    bool isInCheck(Colour colour) const;
    bool isCheckmate(Colour colour) const;
    bool isStalemate(Colour colour) const;

    void print() const;

    // copy constructor
    Board(const Board& other);
    // assignment operator
    Board& operator=(const Board& other);

    Move isMoveLegal(const Move& move) const;
};

#endif // BOARD_H


// TODO:
// movePiece (+ determine move type)
// undo move
// in check, stale, checkmate