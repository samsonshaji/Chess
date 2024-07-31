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
            if (square->getPiece() != nullptr && square->getPiece()->getColour() == colour) {
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

    vector<Move> opponentCaptures;
    Colour opponentColour = (colour == Colour::White) ? Colour::Black : Colour::White;
    //if opponent has capturing moves
    for (const auto& row : board.getBoard()) {
        for (const auto& square : row) {
            if (square->getPiece() != nullptr && square->getPiece()->getColour() != colour) {
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
        vector<Move> movesOutOfDanger;
        for (auto it : opponentCaptures) {
            Piece* ourPiece = it.getTo()->getPiece();
            // we've found our piece. we need to create a move to get out of that square
            for (auto ourMove : legalMoves) {
                if (ourMove.getFrom()->getPiece() == ourPiece) {
                    movesOutOfDanger.push_back(ourMove);
                }
            }
        }

        if (movesOutOfDanger.size() > 0) {
            // check if we have any moves that can capture an opposing piece, or give a check
            vector<Move> capturesOutOfDanger;
            vector<Move> checksOutOfDanger;

            for (auto ourMove : movesOutOfDanger) {
                board.overrideMovePiece(ourMove);
                if (board.isInCheck(opponentColour)) {
                    checksOutOfDanger.push_back(ourMove);
                }
                board.undoMove();
            }

            // priority to checking moves that capture as well
            if (checksOutOfDanger.size() > 0) {
                for (auto ourMove : checksOutOfDanger) {
                    if (ourMove.getTo()->getPiece() != nullptr) {
                        capturesOutOfDanger.push_back(ourMove);
                    }
                }
                if (capturesOutOfDanger.size() > 0) {
                    randomIndex = rand() % capturesOutOfDanger.size();
                    m = capturesOutOfDanger[randomIndex];
                }
                //if no checking captures, randomly select any checking move
                else {
                    randomIndex = rand() % checksOutOfDanger.size();
                    m = checksOutOfDanger[randomIndex];
                }
            }

            // otherwise, randomly select a capturing move if available
            // select a random legal move otherwise
            else {
                for (auto ourMove : movesOutOfDanger) {
                    if (ourMove.getTo()->getPiece() != nullptr) {
                        capturesOutOfDanger.push_back(ourMove);
                    }
                }
                if (capturesOutOfDanger.size() > 0) {
                    randomIndex = rand() % capturesOutOfDanger.size();
                    m = capturesOutOfDanger[randomIndex];
                }
                else {
                    randomIndex = rand() % movesOutOfDanger.size();
                    m = movesOutOfDanger[randomIndex];
                }
            }
            return m;
        }
    }

    //if none of our pieces are under attack
    //priority to checking moves that capture as well
    vector<Move> checks;
    vector<Move> captures;
    
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
