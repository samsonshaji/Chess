#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Robot : public Player {
protected:
    Board *board;
    std::vector<Move> moveList;
    virtual void generateMoves() = 0;
public:
    Robot(Colour c, Board *b);
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
    int getMoveListSize();
    virtual ~Robot() = 0;
    virtual bool isRobot() override;
};

#endif