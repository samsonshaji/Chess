#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"
#include "board.h"
#include "colour.h"
#include <string>

using namespace std;

//abstract class for any player

class Player {
    protected:
        Colour colour;
    public:
        Player(Colour c);

        // Pure virtual function, different logic for human and each robot
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
        
        // Pure virtual destructor, since we use base class pointers for players
        virtual ~Player() = 0;

        //returns a different value based off of the type of player
        virtual bool isRobot() = 0;

        //getter
        Colour getColour() const;
};

#endif 