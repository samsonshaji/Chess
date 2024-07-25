#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"
#include "Board.h"

class Player {
    Color color;
public:
    Player(Color c): color{c} {}
    virtual Color getColor() const = 0;
    virtual Move makeMove(const Board &board) = 0;
};

#endif // PLAYER_H
