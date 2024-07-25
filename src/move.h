#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <vector>
#include <string>

#include "square.h"
#include "movetype.h"

class Move {
    public:
        Square from;
        Square to;
        Move(Square from, Square to);
        Move();

        MoveType getMoveType() const;

        void execute();
        void undo();
};

#endif