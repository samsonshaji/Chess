#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"
#include "Board.h"
#include "Colour.h"

class Player {
    Colour colour;
public:
    Player(Colour c): colour{c} {}
    virtual Colour getColour() const = 0;
    virtual Move makeMove(const Board &board) = 0;
};

#endif // PLAYER_H
