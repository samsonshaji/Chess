#include "robotLevelTwo.h"

LevelTwo::LevelTwo(Colour c, Board *b) : Robot(c, b) {}

LevelTwo::~LevelTwo() {}

Move LevelTwo::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    // generate moves
    std::srand(std::time(0));
    bool legal = false;
    Move m;
    
    std::vector <Move> allMoves;
    for (const auto& row : board.getBoard()) {
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
            }
        }
    }

    // filter out illegal moves
    std::vector<Move> legalMoves;
    for (auto it : allMoves) {
        if (board.isMoveLegal(it)) {
            legalMoves.push_back(it);
        }
    }

    int randomIndex = rand() % legalMoves.size();

    vector<Move> checks;
    vector<Move> captures;
    Colour opponentColour = (colour == Colour::White) ? Colour::Black : Colour::White;

    //if legal moves have checking moves
    for (auto it : legalMoves) {
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
        for (auto it : legalMoves) {
            if (it.getTo()->getPiece() != nullptr) {
                captures.push_back(it);
            }
        }
        if (captures.size() > 0) {
            randomIndex = rand() % captures.size();
            m = captures[randomIndex];
        }
        else {
            randomIndex = rand() % legalMoves.size();
            m = legalMoves[randomIndex];
        }
    }
    
    return m;
}