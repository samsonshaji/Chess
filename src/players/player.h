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
        Colour getColour() const { return colour; }
        // virtual Move makeMove(const Board &board) = 0;
        virtual ~Player();
};

#endif 
