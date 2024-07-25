#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard {
public:
    Scoreboard();
    void updateScore(bool isWhiteWinner);
    void displayScores() const;
private:
    int whiteScore;
    int blackScore;
};

#endif // SCOREBOARD_H
