#ifndef PIECE_H
#define PIECE_H

#include "Colour.h"
#include "PieceType.h"
#include <vector>

class Square;
class Board;
class Move;

class Piece {
protected:
    Colour colour;
    bool hasMoved;
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
    void setBoard(Board *b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
};

#endif 
