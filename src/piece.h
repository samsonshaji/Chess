#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "colour.h"

class Piece {
public:
    Piece(Colour colour);
    virtual ~Piece() = default;
    virtual bool isMoveValid(int startX, int startY, int endX, int endY, const Board& board) const = 0;
    Colour getColour() const;
    virtual std::string getSymbol() const = 0;
private:
    Colour colour;
};

#endif // PIECE_H
