#include "robotLevelOne.h"

LevelOne::LevelOne(Colour c, Board *b) : Robot(c, b) {}

void LevelOne::generateMoves() {
    moveList.clear();

    vector<Move> moves;
    if (colour == Colour::White) {
        //loop through whitePieces with auto
        for (auto it : board->getWhitePieces()) {
            //check if piece has a square
            if (it->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = it->getValidMoves();
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    else {
        //loop through blackPieces with auto
        for (auto it : board->getBlackPieces()) {
            //check if piece has a square
            if (it->getSquare() != nullptr) {
                std::vector<Move> pieceMoves = it->getValidMoves();
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    // make sure all moves here are valid
    for (auto move : moves) {
        if (board->isMoveLegal(move)) {
            moveList.push_back(move);
        }
    }

    cout<<"end1"<<endl;
}

Move LevelOne::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    std::srand(std::time(0));

    while (!legal){

        std::size_t randomIndex = rand() % getMoveListSize();
        std::cout << "Random Index: " << randomIndex << std::endl;
        cout<<"end2"<<endl;
        cout << moveList.size() << endl;

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
