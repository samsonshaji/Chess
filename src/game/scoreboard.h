#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

class ScoreBoard {
    private:
        //track each player's score
        float whiteScore;
        float blackScore;
    public:
        ScoreBoard();
        ~ScoreBoard();

        //update score based on game result
        void updateScore(bool isWhiteWinner);
        //display score at the end of the program
        void displayScore() const;

        //update score based on stalemate
        void stalemateUpdate();
};  

#endif