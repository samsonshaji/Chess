#include "robot.h"

int Robot::getMoveListSize() {
    return moveList.size();
}

Robot::Robot(Colour c, Board *b) : Player(c), board{b} {}

Robot::~Robot() {}