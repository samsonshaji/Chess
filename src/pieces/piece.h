#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecetype.h"
#include <vector>
#include <memory>

class Square;
class Board;
class Move;

class Piece {
protected:
    Colour colour;
    bool hasMoved = false;
    PieceType type;
    char symbol;
    std::shared_ptr<Square>square;
    std::shared_ptr<Board>board;

public:
    virtual ~Piece() = 0;
    PieceType getPieceType() const;
    virtual std::vector<Move> getValidMoves() const = 0;
    void addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const;
    Colour getColour() const;
    void setColour(Colour c);
    Piece(Colour c);
    void setSquare(std::shared_ptr<Square>s);
    void setBoard(std::shared_ptr<Board>b);
    bool getHasMoved() const;
    void setHasMoved(bool m);
    char getSymbol() const;
    std::shared_ptr<Square>getSquare() const;
    bool operator==(const Piece &other) const;
};

#endif 
