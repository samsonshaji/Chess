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
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << whiteScore << std::endl;
    std::cout << "Black: " << blackScore << std::endl;
}

void ScoreBoard::stalemateUpdate() {
    whiteScore += 0.5;
    blackScore += 0.5;
}

ScoreBoard::~ScoreBoard() {
}