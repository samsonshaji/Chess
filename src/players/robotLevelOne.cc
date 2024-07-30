#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves() {
    std::cout << "robot: generateMoves called" << std::endl;
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
    std::cout << "robot: generateMoves finished" << std::endl;
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    std::srand(std::time(0));

    std::cout << "robot: makeMove called" << std::endl;

    // PROBLEM in this function
    while (!legal){

        int randomIndex = rand() % getMoveListSize();

        //check if move is Promotion movetype

        std::cout << "robot: checking if move is promotion" << std::endl;
        if (moveList[randomIndex].getMoveType() == MoveType::Promotion) {
            std::cout << "robot: move is promotion" << std::endl;
            //randomly select a char value from q, n, b, r
            std::string promoteOptions = "qnbr";
            int randomPromoteIndex = rand() % promoteOptions.size();
            char promoteChar = promoteOptions[randomPromoteIndex];
            moveList[randomIndex].setPromotedTo(promoteChar);
            std::cout << "robot: set promotion char: " << promoteChar << std::endl;
        }

        std::cout << "robot: calling isMoveLegal" << std::endl;
        legal = board.isMoveLegal(moveList[randomIndex]); // seg fault here

        if (legal) {
            std::cout << "robot: move is legal... setting m" << std::endl;
            m = moveList[randomIndex];
            std::cout << "robot: makeMove finished" << std::endl;
            return m;
            // std::cout << "Good Move: " << m.getFrom()->getPiece()->getSymbol() <<" (" << m.getFrom()->getX() << "," << m.getFrom()->getY() << ") -> (" << m.getTo()->getX() << "," << m.getTo()->getY() << ") : " << m.getMoveType() << std::endl;
        }
        else {
            std::cout << "robot: move is not legal... erasing from moveList" << std::endl;
            moveList.erase(moveList.begin() + randomIndex);
            continue;
            // cout << "Bad Move: " << moveList[randomIndex].getFrom()->getPiece()->getSymbol() <<" (" << moveList[randomIndex].getFrom()->getX() << "," << moveList[randomIndex].getFrom()->getY() << ") -> (" << moveList[randomIndex].getTo()->getX() << "," << moveList[randomIndex].getTo()->getY() << ") : " << moveList[randomIndex].getMoveType() << endl;
        }

    }
    // std::cout << "robot: makeMove finished" << std::endl;
    return m;
}
