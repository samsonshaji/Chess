#include "robotLevelOne.h"
#include "move.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves() {
    moveList.clear();
    if (colour == Colour::White) {
        for (std::vector<Piece*>::iterator it = board->getWhitePieces().begin(); it != board->getWhitePieces().end(); it++) {
            //check if piece has a square
            if ((*it)->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = (*it)->getAllMoves();
                moveList.insert(moveList.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    else {
        for (std::vector<Piece*>::iterator it = board->getBlackPieces().begin(); it != board->getBlackPieces().end(); it++) {
            //check if piece has a square
            if ((*it)->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = (*it)->getAllMoves();
                moveList.insert(moveList.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
}

Move LevelOne::makeMove(const Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    //randomly select a move
    std::srand(std::time(0));
    int randomIndex = rand() % getMoveListSize();


    //check if move is Promotion movetype
    if (moveList[randomIndex].getMoveType() == MoveType::Promotion) {
        //randomly select a char value from q, n, b, r
        std::string promoteOptions = "qnbr";
        int randomPromoteIndex = rand() % promoteOptions.size();
        char promoteChar = promoteOptions[randomPromoteIndex];
        moveList[randomIndex].setPromotedTo(promoteChar);
    }

    Move m;
    m = moveList[randomIndex];

    return m;
}