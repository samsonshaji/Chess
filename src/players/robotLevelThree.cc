#include "robotLevelThree.h"

LevelThree::LevelThree(Colour c, Board *b) : Robot(c, b) {}

LevelThree::~LevelThree() {}

Move LevelThree::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    // generate moves
    std::srand(std::time(0));
    bool legal = false;
    Move m;
    
    std::vector <Move> allMoves;
    for (const auto& row : board.getBoard()) {
        for (const auto& square : row) {
            if (square->getPiece() != nullptr && square->getPiece()->getColour() != colour) {
                std::vector<Move> moves = square->getPiece()->getValidMoves();
                for (auto it : moves) {
                    MoveType mt = board.determineMoveType(it);
                    if (mt == MoveType::Promotion) {
                        it.setPromotedTo('q'); // always promote to Q
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
    Move currMove = legalMoves[randomIndex];

    vector<Move> checks;
    vector<Move> captures;
    vector<Move> opponentCaptures;
    Colour opponentColour = (colour == Colour::White) ? Colour::Black : Colour::White;

    //if legal moves have checking moves
    for (auto it : legalMoves) {
        board.overrideMovePiece(it);
        if (board.isInCheck(opponentColour))  {
            checks.push_back(it);
        }
        board.undoMove();
    }

    //if legal moves have capturing moves
    for (auto it : legalMoves) {
        if (it.getTo()->getPiece() != nullptr) {
            captures.push_back(it);
        }
    }

    //if opponent has capturing moves
    for (const auto& row : board.getBoard()) {
        for (const auto& square : row) {
            if (square->getPiece() != nullptr && square->getPiece()->getColour() == opponentColour) {
                std::vector<Move> moves = square->getPiece()->getValidMoves();
                for (auto it : moves) {
                    if (it.getTo()->getPiece() != nullptr) {
                        opponentCaptures.push_back(it);
                    }
                }
            }
        }
    }

    //priority to move OUR pieces that are under attack
    if (opponentCaptures.size() > 0) {
        for (auto it : opponentCaptures) {

            Piece* ourPiece = it.getTo()->getPiece();
            // we've found our piece. we need to create a move to get out of that square
            vector<Move> movesOutOfDanger;
            for (auto ourMove : legalMoves) {
                if (ourMove.getFrom()->getPiece() == ourPiece) {
                    movesOutOfDanger.push_back(ourMove);
                }
            }

            if (movesOutOfDanger.size() > 0) {
                // let's see if we have any moves that can capture an opposing piece, or give a check
                for (auto it : movesOutOfDanger) {
                    if (std::find(checks.begin(), checks.end(), it) != checks.end()) {
                        m = it;
                        legal = true;
                        break;
                    }
                    if (std::find(captures.begin(), captures.end(), it) != captures.end()) {
                        m = it;
                        legal = true;
                        break;
                    }
                }
            }

        }
    }



    
    return m;
}