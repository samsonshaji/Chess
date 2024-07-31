#include "robotLevelFour.h"

LevelFour::LevelFour(Colour c, std::shared_ptr<Board>b) : Robot(c, b) {}

LevelFour::~LevelFour() {}

int LevelFour::getPoints(PieceType pt) {
    switch (pt) {
        case PieceType::pawn:
            return 1;
        case PieceType::knight:
            return 3;
        case PieceType::bishop:
            return 3;
        case PieceType::rook:
            return 5;
        case PieceType::queen:
            return 9;
        case PieceType::king:
            return 100;
        default:
            return 0;
    }
}


Move LevelFour::makeMove(Board &board, const string &to, const string &from, const string &promote) {
    // generate moves
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
    for (const auto& row : board.getState()) {
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
            std::shared_ptr<Piece> ourPiece = it.getTo()->getPiece();
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
                    // sort captures by most valuable piece captured
                    std::sort(capturesOutOfDanger.begin(), capturesOutOfDanger.end(), [this](Move a, Move b) {
                        return getPoints(a.getTo()->getPiece()->getPieceType()) > getPoints(b.getTo()->getPiece()->getPieceType());
                    });

                    // select the most valuable capture
                    m = capturesOutOfDanger[0];
                }
                //if no checking captures, randomly select any checking move
                else {
                    randomIndex = rand() % checksOutOfDanger.size();
                    m = checksOutOfDanger[randomIndex];
                }
            }

            
            else {
                for (auto ourMove : movesOutOfDanger) {
                    if (ourMove.getTo()->getPiece() != nullptr) {
                        capturesOutOfDanger.push_back(ourMove);
                    }
                }
                // if available, select a capturing move that wins most material
                if (capturesOutOfDanger.size() > 0) {
                    // sort captures by most valuable piece captured
                    std::sort(capturesOutOfDanger.begin(), capturesOutOfDanger.end(), [this](Move a, Move b) {
                        return getPoints(a.getTo()->getPiece()->getPieceType()) > getPoints(b.getTo()->getPiece()->getPieceType());
                    });

                    // select the most valuable capture
                    m = capturesOutOfDanger[0];
                }
                // otherwise, select a random legal move
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
            // sort captures by most valuable piece captured
            std::sort(captures.begin(), captures.end(), [this](Move a, Move b) {
                return getPoints(a.getTo()->getPiece()->getPieceType()) > getPoints(b.getTo()->getPiece()->getPieceType());
            });

            // select the most valuable capture
            m = captures[0];
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
            // sort captures by most valuable piece captured
            std::sort(captures.begin(), captures.end(), [this](Move a, Move b) {
                return getPoints(a.getTo()->getPiece()->getPieceType()) > getPoints(b.getTo()->getPiece()->getPieceType());
            });

            // select the most valuable capture
            m = captures[0];
        }
        else {
            randomIndex = rand() % legalMoves.size();
            m = legalMoves[randomIndex];
        }
    }
    return m;
}
