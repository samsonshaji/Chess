#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "colour.h"

class Human : public Player {
public:
    Human(Colour colour);
    virtual Colour getColour() const override;
    virtual Move makeMove(const Board &board) override;
};

#endif 