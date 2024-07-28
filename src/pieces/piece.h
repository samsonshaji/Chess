#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecetype.h"
#include <vector>

class Square;
class Board;
class Move;

class Piece {
protected:
    Colour colour;
    bool hasMoved = false;
    PieceType type;
    char symbol;
    Square *square;
    Board *board;

public:
    virtual ~Piece();
    PieceType getPieceType() const;
    virtual std::vector<Move> getValidMoves() const = 0;
    Colour getColour() const;
    Piece(Colour c);
    void setSquare(Square *s);
    Square *getSquare() const;
    void setBoard(Board *b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
};

#endif 
