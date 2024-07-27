#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <vector>
#include <string>

#include "square.h"
#include "movetype.h"

class Move {
    private:
        Square* from;
        Square* to;
        MoveType type;
        Piece *capturedPiece=nullptr;

    public:
        Move(Square* f, Square* t);
        Move(Square* f, Square* t, MoveType mt);

        MoveType getMoveType() const;
        void setMoveType(MoveType t);

        void execute();
        void undo();

        Square* getFrom() const;
        Square* getTo() const;

        Piece* getCapturedPiece() const;
        void setCapturedPiece(Piece* piece);
};

#endif