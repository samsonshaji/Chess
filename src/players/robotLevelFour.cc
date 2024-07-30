#include "robotLevelFour.h"

LevelFour::LevelFour(Colour c, Board *b) : Robot(c, b) {}

LevelFour::~LevelFour() {}

int LevelFour::getPoints(PieceType pt) {
    switch (pt) {
        case PieceType::pawn:
            return 1;
        case PieceType::knight:
            return 3;
        case PieceType::bishop:
            return 3;
        case PieceType::rook:
            return 5;
        case PieceType::queen:
            return 9;
        case PieceType::king:
            return 100;
        default:
            return 0;
    }
}

