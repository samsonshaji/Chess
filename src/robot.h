#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include "move.h"

class Robot : public Player {
public:
    Robot(Colour colour) : Player(colour) {}
    virtual Colour getColour() const override;
    virtual void makeMove(const Board &board) override;
};

#endif