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
    // for (std::vector<Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
    //     std::cout << it->getFrom()->getPiece()->getSymbol() << " (" << it->getFrom()->getX() << "," << it->getFrom()->getY() << ") -> (" << it->getTo()->getX() << "," << it->getTo()->getY() << ") : " << it->getMoveType() << std::endl;
    // }
    cout<<"end1"<<endl;
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    while (!legal){

        //randomly select a move
        std::srand(std::time(0));
        int randomIndex = rand() % getMoveListSize();
        cout<<"end2"<<endl;


        //check if move is Promotion movetype
        if (moveList[randomIndex].getMoveType() == MoveType::Promotion) {
            cout<<"end3"<<endl;
            //randomly select a char value from q, n, b, r
            std::string promoteOptions = "qnbr";
            int randomPromoteIndex = rand() % promoteOptions.size();
            cout << "end3.5" << endl;
            char promoteChar = promoteOptions[randomPromoteIndex];
            moveList[randomIndex].setPromotedTo(promoteChar);
            cout<<"end4"<<endl;
        }
        cout << "--";
        cout << "4.5 Move: " << moveList[randomIndex].getFrom()->getPiece()->getSymbol() <<" (" << moveList[randomIndex].getFrom()->getX() << "," << moveList[randomIndex].getFrom()->getY() << ") -> (" << moveList[randomIndex].getTo()->getX() << "," << moveList[randomIndex].getTo()->getY() << ") : " << moveList[randomIndex].getMoveType() << endl;
        legal = board.isMoveLegal(moveList[randomIndex]);
        cout<<"end5"<<endl;
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
