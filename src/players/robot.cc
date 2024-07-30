#include "robot.h"

Robot::Robot(Colour c, Board *b) : Player(c), board{b} {}

Robot::~Robot() {
    board = nullptr;
}

bool Robot::isRobot() {
    return true;
}
