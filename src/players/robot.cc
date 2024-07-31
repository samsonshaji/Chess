#include "robot.h"

Robot::Robot(Colour c, std::shared_ptr<Board>b) : Player(c), board{b} {}

Robot::~Robot() {
    board = nullptr;
}

bool Robot::isRobot() {
    return true;
}
