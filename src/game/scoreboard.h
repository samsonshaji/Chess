#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

class ScoreBoard {
    private:
        int whiteScore;
        int blackScore;
    public:
        ScoreBoard();
        int getWhiteScore() const;
        int getBlackScore() const;
        void setWhiteScore(int score);
        void setBlackScore(int score);

        void updateScore(bool isWhiteWinner);
        void displayScore() const;
};

#endif