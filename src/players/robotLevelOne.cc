#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves() {
    
    for (const auto &row : board->getBoard()) {
        for (const auto &square : row) {
            Piece *piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getValidMoves();
                moveList.insert(moveList.end(), validMoves.begin(), validMoves.end());
            }

        }
    }
    }

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    std::srand(std::time(0));
    int randomIndex = rand() % getMoveListSize();

    while (!legal){
        randomIndex = rand() % getMoveListSize(); 

        //check if move is Promotion movetype

        if (moveList[randomIndex].getMoveType() == MoveType::Promotion) {
            //randomly select a char value from q, n, b, r
            std::string promoteOptions = "qnbr";
            int randomPromoteIndex = rand() % promoteOptions.size();
            char promoteChar = promoteOptions[randomPromoteIndex];
            moveList[randomIndex].setPromotedTo(promoteChar);
        }

        legal = board.isMoveLegal(moveList[randomIndex]); // seg fault here

        if (legal) {
            m = moveList[randomIndex];
            return m;
        }
        else {
            moveList.erase(moveList.begin() + randomIndex);
            continue;
        }

    }
    std::cout << "Move: " << m.getFrom()->getPiece()->getSymbol() <<" (" << m.getFrom()->getX() << "," << m.getFrom()->getY() << ") -> (" << m.getTo()->getX() << "," << m.getTo()->getY() << ") : " << m.getMoveType() << std::endl;
    return m;
}
