#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, std::shared_ptr<Board>b) : Robot(c, b) {}

LevelOne::~LevelOne() {
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    std::srand(std::time(0));
    bool legal = false;
    Move m;
    
    std::vector <Move> allMoves;
    for (const auto& row : board.getState()) {
        for (const auto& square : row) {
            if (square->getPiece() != nullptr && square->getPiece()->getColour() == colour) {
                std::vector<Move> moves = square->getPiece()->getValidMoves();
                for (auto it : moves) {
                    MoveType mt = board.determineMoveType(it);
                    if (mt == MoveType::Promotion) {
                        std::string promoteOptions = "qnbr";
                        int randomPromoteIndex = rand() % promoteOptions.size();
                        char promoteChar = promoteOptions[randomPromoteIndex];
                        it.setPromotedTo(promoteChar);
                    }
                    it.setMoveType(mt);
                    allMoves.push_back(it);
                }
                moves.clear();
            }
        }
    }

    int randomIndex = rand() % allMoves.size();
    Move currMove = allMoves[randomIndex];

    while (!legal){
        legal = board.isMoveLegal(currMove);

        if (legal) {
            m = currMove;
            return m;
        }
        else {
            allMoves.erase(allMoves.begin() + randomIndex);
            std::cout << std::endl;
            randomIndex = rand() % allMoves.size();
            currMove = allMoves[randomIndex];
        }

    }
    allMoves.clear();
    return m;
}
