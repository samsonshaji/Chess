#include "robotLevelTwo.h"

LevelTwo::LevelTwo(Colour c, Board *b) : Robot(c, b) {}

LevelTwo::~LevelTwo() {}

void LevelTwo::generateMoves() {
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

    //filter out illegal moves
    for (auto it : moves) {
        if(board->isMoveLegal(it)) {
            moveList.push_back(it);
        }
    }
}

Move LevelTwo::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    generateMoves();
    bool legal = false;
    Move m;

    std::srand(std::time(0));
    int randomIndex;

    vector<Move> checks;
    vector<Move> captures;
    Colour opponentColour = (colour == Colour::White) ? Colour::Black : Colour::White;

    //if legal moves have checking moves
    for (auto it : moveList) {
        board.overrideMovePiece(it);
        if (board.isInCheck(opponentColour))  {
            checks.push_back(it);
        }
        board.undoMove();
    }

    //priority to checking moves that capture as well
    if (checks.size() > 0) {
        for (auto it : checks) {
            if (it.getTo()->getPiece() != nullptr) {
                captures.push_back(it);
            }
        }
        if (captures.size() > 0) {
            randomIndex = rand() % captures.size();
            m = captures[randomIndex];
        }
        //if no checking captures, randomly select any checking move
        else {
            randomIndex = rand() % checks.size();
            m = checks[randomIndex];
        }
    }
    //otherwise, randomly select a capturing move if available
    //select a random legal move otherwise
    else {
        for (auto it : moveList) {
            if (it.getTo()->getPiece() != nullptr) {
                captures.push_back(it);
            }
        }
        if (captures.size() > 0) {
            randomIndex = rand() % captures.size();
            m = captures[randomIndex];
        }
        else {
            randomIndex = rand() % moveList.size();
            m = moveList[randomIndex];
        }
    }

        //check if move is Promotion movetype
    if (m.getMoveType() == MoveType::Promotion) {
        //randomly select a char value from q, n, b, r
        std::string promoteOptions = "qnbr";
        int randomPromoteIndex = rand() % promoteOptions.size();
        char promoteChar = promoteOptions[randomPromoteIndex];
        m.setPromotedTo(promoteChar);
    }
 
    std::cout << "Move: " << m.getFrom()->getPiece()->getSymbol() <<" (" << m.getFrom()->getX() << "," << m.getFrom()->getY() << ") -> (" << m.getTo()->getX() << "," << m.getTo()->getY() << ") : " << m.getMoveType() << std::endl;
    
    return m;
}