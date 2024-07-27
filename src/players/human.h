#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "colour.h"
#include "move.h"
#include "board.h"

class Human : public Player {
public:
    Human(Colour colour);
    virtual Move makeMove(const Board &board) override;
};

#endif 