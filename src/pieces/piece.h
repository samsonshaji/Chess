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
    void addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const;
    Colour getColour() const;
    void setColour(Colour c);
    Piece(Colour c);
    void setSquare(Square *s);
    void setBoard(Board *b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
    Square *getSquare() const;
    bool operator==(const Piece &other) const;
};

#endif 
