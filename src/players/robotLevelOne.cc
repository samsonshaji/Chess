#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves(std::vector<Move> &allValidMoves) {
    std::cout << "robot: generateMoves called" << std::endl;
    
    for (const auto &row : board->getBoard()) {
        for (const auto &square : row) {
            Piece *piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getValidMoves();
                moveList.insert(moveList.end(), validMoves.begin(), validMoves.end());
            }

        }
    }
    
    std::cout << "robot: allValidMoves.size(): " << allValidMoves.size() << std::endl;
    std::cout << "robot: generateMoves finished" << std::endl;
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    std::vector<Move> allValidMoves;
    generateMoves(allValidMoves);
    bool legal = false;
    Move m;

    std::cout << "robot: makeMove called" << std::endl;

    std::srand(std::time(0));
    int randomIndex = rand() % getMoveListSize();

    // PROBLEM in this function
    while (!legal){
        std::cout << "robot: in while loop" << std::endl;
        std::cout << "robot: getMoveListSize(): " << getMoveListSize() << std::endl;
        randomIndex = rand() % getMoveListSize(); // floating point exception happens here
        std::cout << "robot: randomIndex: " << randomIndex << std::endl;

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
            std::cout << "before erase: " << moveList.size() << std::endl;
            moveList.erase(moveList.begin() + randomIndex);
            std::cout << "after erase: " << moveList.size() << std::endl;
            std::cout << "erased" << std::endl;
            continue;
            // cout << "Bad Move: " << moveList[randomIndex].getFrom()->getPiece()->getSymbol() <<" (" << moveList[randomIndex].getFrom()->getX() << "," << moveList[randomIndex].getFrom()->getY() << ") -> (" << moveList[randomIndex].getTo()->getX() << "," << moveList[randomIndex].getTo()->getY() << ") : " << moveList[randomIndex].getMoveType() << endl;
        }

    }
    // std::cout << "robot: makeMove finished" << std::endl;
    return m;
}
