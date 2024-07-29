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
        char promotedTo;
        MoveType pawnSecondary;

    public:
        Move();
        Move(Square* f, Square* t);
        
        Move& operator=(const Move& m);

        MoveType getMoveType() const;
        void setMoveType(MoveType t);

        MoveType getPawnSecondary() const;
        void setPawnSecondary(MoveType t);

        Square* getFrom() const;
        Square* getTo() const;

        char getPromotedTo() const;
        void setPromotedTo(char c);

        bool operator==(const Move& m) const;

};

#endif