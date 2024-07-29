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
    bool enPassantable = false;
    void addDirectionalMoves(std::vector<Move>& moves, int xDir, int yDir) const;

public:
    virtual ~Piece();
    PieceType getPieceType() const;
    virtual std::vector<Move> getAllMoves() const = 0;
    Colour getColour() const;
    Piece(Colour c);
    void setSquare(Square *s);
    Square *getSquare() const;
    void setBoard(Board *b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
    bool operator==(const Piece &other) const;
    bool getEnPassantable() const;
    void setEnPassantable(bool e);
};

#endif 
