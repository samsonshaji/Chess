#ifndef PIECE_H
#define PIECE_H

#include "Move.h"
#include "Board.h"
#include "Colour.h"
#include "PieceType.h"
#include <vector>

class Piece {
protected:
    Colour colour;
    bool hasMoved;
public:
    virtual ~Piece() = default;
    virtual PieceType getType() const = 0;
    virtual std::vector<Move> getMoveStack() const = 0;
    virtual bool isMoveValid(const Move &m, const Board &board) const = 0;
    virtual int getPoints() const = 0;
    virtual PieceType getPieceType() const = 0;
    virtual bool isPinned(const Board &b) const = 0;
    virtual bool canCheck(const Board &b) const = 0;
    virtual void move(const Move &m) = 0;
    virtual bool hasMoved() const;
    Colour getColour() const;
};

#endif 
