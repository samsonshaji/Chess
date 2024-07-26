#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

class ScoreBoard {
    private:
    public:
        int getWhiteScore() const;
        int getBlackScore() const;
        void setWhiteScore(int score);
        void setBlackScore(int score);

        void updateScore(int whiteScore, int blackScore);
        void displayScore() const;
};

#endif