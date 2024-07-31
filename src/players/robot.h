#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <vector>

//abstract class for robots

class Robot : public Player {
protected:
    std::shared_ptr<Board>board;
public:
    // Constructor
    Robot(Colour c, std::shared_ptr<Board>b);
    //make move function, different for each level of robot
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
    // Pure virtual destructor, since we use base class pointers for robots
    virtual ~Robot() = 0;
    // Returns true
    virtual bool isRobot() override;
};

#endif