#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves() {
    moveList.clear();

    if (colour == Colour::White) {
        //loop through whitePieces with auto
        for (auto it : board->getWhitePieces()) {
            //check if piece has a square
            if (it->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = it->getValidMoves();
                moveList.insert(moveList.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    else {
        //loop through blackPieces with auto
        for (auto it : board->getBlackPieces()) {
            //check if piece has a square
            if (it->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = it->getValidMoves();
                moveList.insert(moveList.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    std::srand(std::time(0));

    while (!legal){

        int randomIndex = rand() % getMoveListSize();

        //check if move is Promotion movetype
        if (moveList[randomIndex].getMoveType() == MoveType::Promotion) {
            //randomly select a char value from q, n, b, r
            std::string promoteOptions = "qnbr";
            int randomPromoteIndex = rand() % promoteOptions.size();
            char promoteChar = promoteOptions[randomPromoteIndex];
            moveList[randomIndex].setPromotedTo(promoteChar);
        }
        legal = board.isMoveLegal(moveList[randomIndex]);
        if (legal) {
            m = moveList[randomIndex];
            std::cout << "Good Move: " << m.getFrom()->getPiece()->getSymbol() <<" (" << m.getFrom()->getX() << "," << m.getFrom()->getY() << ") -> (" << m.getTo()->getX() << "," << m.getTo()->getY() << ") : " << m.getMoveType() << std::endl;
        }
        else {
            moveList.erase(moveList.begin() + randomIndex);
            cout << "Bad Move: " << moveList[randomIndex].getFrom()->getPiece()->getSymbol() <<" (" << moveList[randomIndex].getFrom()->getX() << "," << moveList[randomIndex].getFrom()->getY() << ") -> (" << moveList[randomIndex].getTo()->getX() << "," << moveList[randomIndex].getTo()->getY() << ") : " << moveList[randomIndex].getMoveType() << endl;
        }

    }
    return m;
}
