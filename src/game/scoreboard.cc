#include "scoreboard.h"
#include <iostream>

Scoreboard::Scoreboard() : whiteScore(0), blackScore(0) {}

void Scoreboard::updateScore(bool isWhiteWinner) {
    if (isWhiteWinner) {
        ++whiteScore;
    } else {
        ++blackScore;
    }
}

void Scoreboard::displayScores() const {
    std::cout << "White: " << whiteScore << " Black: " << blackScore << std::endl;
}
