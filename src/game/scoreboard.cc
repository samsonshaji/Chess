#include "scoreboard.h"
#include <iostream>

ScoreBoard::ScoreBoard() : whiteScore(0), blackScore(0) {}

void ScoreBoard::updateScore(bool isWhiteWinner) {
    if (isWhiteWinner) {
        ++whiteScore;
    } else {
        ++blackScore;
    }
}

void ScoreBoard::displayScore() const {
    std::cout << "White: " << whiteScore << " Black: " << blackScore << std::endl;
}
