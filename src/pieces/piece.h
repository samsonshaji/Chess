#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecetype.h"
#include <vector>

class Square;
class Board;
class Move;


// Abstract class for all pieces
class Piece {
protected:
    Colour colour;
    // flag used for piece behaviour logic
    // for example, used to determine if a piece can castle or if a pawn can move two squares
    bool hasMoved = false;
    // type of piece
    PieceType type;
    //visual display based off colour
    char symbol;
    //pointer to square piece is on
    Square *square;
    Board *board;

public:
    // Pure virtual destructor, since we point to pieces with base class pointers
    virtual ~Piece() = 0;
    // Pure virtual function to get all possible moves for a piece, different behaviour for each piece
    virtual std::vector<Move> getValidMoves() const = 0;
    // adds behaviour for a piece that can move beyond one square in a direction
    void addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const;
    //construct with colour
    Piece(Colour c);
    //overload equality operator for vector and other piece comparisons
    bool operator==(const Piece &other) const;

    //getters and setters
    void setSquare(Square *s);
    void setBoard(Board *b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
    Square *getSquare() const;
    Colour getColour() const;
    PieceType getPieceType() const;
};

#endif 
