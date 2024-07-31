#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecetype.h"
#include <vector>
#include <memory>

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

    // pointer to square piece is on
    std::shared_ptr<Square>square;
    std::shared_ptr<Board>board;

public:
    // Pure virtual destructor, since we point to pieces with base class pointers
    virtual ~Piece() = 0;
    // Pure virtual function to get all possible moves for a piece, different behaviour for each piece
    virtual std::vector<Move> getValidMoves() const = 0;
    // adds behaviour for a piece that can move beyond one square in a direction
    void addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const;
    //construct with colour
    Piece(Colour c);
    void setSquare(std::shared_ptr<Square>s);
    void setBoard(std::shared_ptr<Board>b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
    std::shared_ptr<Square>getSquare() const;
    bool operator==(const Piece &other) const;
    Colour getColour() const;
    PieceType getType() const;
    PieceType getPieceType() const;
};

#endif 
