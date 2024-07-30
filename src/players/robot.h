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
    virtual void generateMoves(std::vector<Move> &allValidMoves) = 0;
public:
    Robot(Colour c, Board *b);
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
    int getMoveListSize();
    virtual ~Robot();
    virtual bool isRobot() override;
};

#endif