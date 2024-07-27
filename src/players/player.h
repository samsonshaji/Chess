#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"
#include "board.h"
#include "colour.h"

class Player {
    protected:
        Colour colour;
    public:
        Player(Colour c): colour{c} {}
        virtual Colour getColour() const = 0;
        virtual Move makeMove(const Board &board) = 0;
};

#endif 
