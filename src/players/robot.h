#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include "move.h"

class Robot : public Player {
public:
    Robot(Colour c);
    virtual Move makeMove(const Board &board) override = 0;
};

#endif