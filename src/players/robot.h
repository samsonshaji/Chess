#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include "move.h"

class Robot : public Player {
    Colour c;
    int level;
    Robot *robot;
public:
    Robot(Colour c, int level);
    virtual Colour getColour() const override;
    virtual Move makeMove(const Board &board) override = 0;
};

#endif