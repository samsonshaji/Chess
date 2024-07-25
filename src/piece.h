#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "move.h"

enum class PieceType { King, Queen, Rook, Bishop, Knight, Pawn };
enum class Color { White, Black };

class Piece {
public:
    virtual bool isMoveValid(Move m, const Board &b) const = 0;
    virtual PieceType getType() const = 0;
    virtual ~Piece() {}
    Color getColor() const { return color; }
    void setColor(Color c) { color = c; }
    virtual std::string toString() const = 0;
    virtual std::string toGraphics() const = 0;
    virtual Piece* clone() const = 0;
    virtual bool hasMoved() const = 0;
    virtual void setMoved() = 0;
    virtual void move(Move m, Board &b) = 0;
    virtual bool isAttackingSquare(Move m, const Board &b) const = 0;
    virtual bool isPinned(const Board &b) const = 0;
    virtual bool isCheckingSquare(Move m, const Board &b) const = 0;
    virtual int getPoints() const = 0;
    virtual bool canCheck(const Board &b) const = 0;

    friend std::ostream &operator<<(std::ostream &out, const Piece &p);
protected:
    Color color;
};

#endif // PIECE_H
