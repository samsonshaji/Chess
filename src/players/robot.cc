#include "robot.h"
#include "robotLevelOne.h"
#include "robotLevelTwo.h"
#include "robotLevelThree.h"
#include "robotLevelFour.h"

Robot::Robot(Colour c, int level) : c{c}, level{level} {
    if (level == 1) {
        robot = new LevelOne();
    } else if (level == 2) {
        robot = new LevelTwo();
    } else if (level == 3) {
        robot = new LevelThree();
    } else if (level == 4) {
        robot = new LevelFour();
    }
}

Colour Robot::getColour() const {
    return c;
}

Robot::~Robot() {
    delete robot;
}