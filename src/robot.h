#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include "move.h"

class Robot : public Player {
    public: 
        virtual Move makeMove(const Board& board) = 0;
};

#endif