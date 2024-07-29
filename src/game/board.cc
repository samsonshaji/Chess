#include "board.h"
#include <iostream>
#include <algorithm>
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "colour.h"
#include "move.h"
#include "square.h"

using namespace std;

Board::Board() {
    setupInitialBoard();
}

Board::~Board() {
    clearBoard();
    for (auto& row : board) {
        for (auto& s : row) {
            delete s;
        }
    }
}

void Board::print() const {
    string space = " ";
    cout << " " << endl;
    cout << "    abcdefgh" << endl;
    cout << " " << endl;
    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << "   ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getPiece() == nullptr) {
                std::cout << space;
            } else {
                std::cout << board[i][j]->getPiece()->getSymbol();
            }
            space = (space == " ") ? "_" : " ";
        }
        std::cout << "" << std::endl;
        space = (space == " ") ? "_" : " ";
    }
    cout << " " << endl;
}

void Board::clearBoard() {

    for (auto row : board) {
        for (auto square : row) {
            square->removePiece();
        }
    }

    if (whitePieces.size() != 0 || blackPieces.size() != 0) {
        //loop through whitePieces and blackPieces and delete each piece
        for (auto piece : whitePieces) {
            delete piece;
        }
        for (auto piece : blackPieces) {
            delete piece;
        }
    }

    //clear whitePieces and blackPieces
    whitePieces.clear();
    blackPieces.clear();
}

void Board::setupInitialBoard() {

    for (int i = 0; i < 8; i++) {
        std::vector<Square*> row;
        for (int j = 0; j < 8; j++) {
            Square* s = new Square(j, i);
            s->setBoard(this);
            row.push_back(s);
        }
        board.push_back(row);
    }

    // calls square's setPiece function
    // white pieces
    board[0][0]->setPiece(new Rook(Colour::White));
    board[0][1]->setPiece(new Knight(Colour::White));
    board[0][2]->setPiece(new Bishop(Colour::White));
    board[0][3]->setPiece(new Queen(Colour::White));
    board[0][4]->setPiece(new King(Colour::White));
    board[0][5]->setPiece(new Bishop(Colour::White));
    board[0][6]->setPiece(new Knight(Colour::White));
    board[0][7]->setPiece(new Rook(Colour::White));
    for (int i = 0; i < 8; i++) {
        board[1][i]->setPiece(new Pawn(Colour::White));
        whitePieces.push_back(board[1][i]->getPiece());
        whitePieces.push_back(board[0][i]->getPiece());
    }

    // black pieces
    board[7][0]->setPiece(new Rook(Colour::Black));
    board[7][1]->setPiece(new Knight(Colour::Black));
    board[7][2]->setPiece(new Bishop(Colour::Black));
    board[7][3]->setPiece(new Queen(Colour::Black));
    board[7][4]->setPiece(new King(Colour::Black));
    board[7][5]->setPiece(new Bishop(Colour::Black));
    board[7][6]->setPiece(new Knight(Colour::Black));
    board[7][7]->setPiece(new Rook(Colour::Black));
    for (int i = 0; i < 8; i++) {
        board[6][i]->setPiece(new Pawn(Colour::Black));
        blackPieces.push_back(board[6][i]->getPiece());
        blackPieces.push_back(board[7][i]->getPiece());
    }
}

std::vector<Piece*> Board::getWhitePieces() const {
    return whitePieces;
}

std::vector<Piece*> Board::getBlackPieces() const {
    return blackPieces;
}

void Board::removePiece(Square* square) {
    square->removePiece();
}

// void Board::deletePiece(Square* square) {
//     //remove piece from blackPieces or whitePieces
//     Piece* piece = square->getPiece();
//     if (piece->getColour() == Colour::White) {
//         auto it = std::find(whitePieces.begin(), whitePieces.end(), piece);
//         if (it != whitePieces.end()) {
//             whitePieces.erase(it);
//         }
//     } else {
//         auto it = std::find(blackPieces.begin(), blackPieces.end(), piece);
//         if (it != blackPieces.end()) {
//             blackPieces.erase(it);
//         }
//     }
//     square->deletePiece();
    
// }

std::vector<std::vector<Square*>> Board::getState() const {
    return board;
}

Square* Board::getSquare(int x, int y) const {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return nullptr;
    }
    return board[y][x];
}

void Board::setController(Controller* ctrl) {
    controller = ctrl;
}

Square* Board::findKing(Colour colour) const {
    // std::cout << "findKing called" << std::endl;
    if (colour == Colour::White) {
        for (const auto& piece : whitePieces) {
            if (piece->getPieceType() == PieceType::king) {
                return piece->getSquare();
            }
        }
    }
    else{
        for (const auto& piece : blackPieces) {
            if (piece->getPieceType() == PieceType::king) {
                return piece->getSquare();
            }
        }
    }
    // not found -- should never happen
    return nullptr;
}

Move Board::isMoveLegal(const Move& move) const {
    Colour current = controller->getCurrentPlayer()->getColour();
    Piece* piece = move.getFrom()->getPiece();

    vector<Move> allMoves = piece->getAllMoves();
    //print all moves
    for (const auto& m : allMoves) {
        std::cout << "Move: " << m.getFrom()->getX() << " " << m.getFrom()->getY() << " to " << m.getTo()->getX() << " " << m.getTo()->getY() << " " << m.getMoveType() << std::endl;
    }
    //using find(), check if move is in allMoves
    auto it = find(allMoves.begin(), allMoves.end(), move);
    if (it != allMoves.end()) {
        it->setPromotedTo(move.getPromotedTo());
        //create a copy of the board
        return *it;
        // Board *test = new Board(*this);
        // bool x = test->movePiece(*it, true);
    }
    return Move(nullptr, nullptr);
}

bool Board::isValidSetup() const {
    // check if there is exactly one king of each color
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece) {
                if (piece->getPieceType() == PieceType::king) {
                    if (piece->getColour() == Colour::White) {
                        whiteKingCount++;
                    } else {
                        blackKingCount++;
                    }
                }
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1) {
        return false;
    }

    // check if there are no pawns on the first or last row
    for (int i = 0; i < 8; i++) {
        if (board[0][i]->getPiece() && board[0][i]->getPiece()->getPieceType() == PieceType::pawn) {
            return false;
        }
        if (board[7][i]->getPiece() && board[7][i]->getPiece()->getPieceType() == PieceType::pawn) {
            return false;
        }
    }

    // check if there are no more than 8 pawns of each color
    int whitePawnCount = 0;
    int blackPawnCount = 0;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getPieceType() == PieceType::pawn) {
                if (piece->getColour() == Colour::White) {
                    whitePawnCount++;
                } else {
                    blackPawnCount++;
                }
            }
        }
    }

    if (whitePawnCount > 8 || blackPawnCount > 8) {
        return false;
    }

    // ensure neither king is in check
    if (isInCheck(Colour::White) || isInCheck(Colour::Black)) {
        return false;
    }

    return true;
}


bool Board::movePiece(const Move& move, bool test) {
    Move ourMove;
    ourMove = move;
    if (!test) {
        ourMove = isMoveLegal(move);

        if (ourMove.getFrom() == nullptr || ourMove.getTo() == nullptr) {
            cout << "Invalid move" << endl;
            return false;
        }
    }

    Colour current = controller->getCurrentPlayer()->getColour();

    Square* from = ourMove.getFrom();
    Square* to = ourMove.getTo();
    Piece* piece = from->getPiece();
    piece->setHasMoved(true);


    // Handle castling
    if (ourMove.getMoveType() == MoveType::Castling) {
        if (to->getX() == from->getX() + 2) {
            // Kingside castling
            Square* rookFrom = getSquare(7, from->getY());
            Square* rookTo = getSquare(5, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->removePiece();
            rookTo->setPiece(rook);
            rook->setHasMoved(true);
        } else if (to->getX() == from->getX() - 2) {
            // Queenside castling
            Square* rookFrom = getSquare(0, from->getY());
            Square* rookTo = getSquare(3, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->removePiece();
            rookTo->setPiece(rook);
            rook->setHasMoved(true);
        }
    }

    // Handle en passant
    if (ourMove.getMoveType() == MoveType::EnPassant) {
        Square* captured = getSquare(to->getX(), to->getY() - (piece->getColour() == Colour::White ? 1 : -1));
        captured->removePiece();
    }

    
    if (ourMove.getMoveType() == MoveType::DoublePawn) {
        piece->setEnPassantable(true);
    }

    from->removePiece();

    if (ourMove.getMoveType() == MoveType::Capture) {
        to->removePiece();
    }

    to->setPiece(piece);

    // Handle promotion
    if (ourMove.getMoveType() == MoveType::Promotion || ourMove.getPawnSecondary() == MoveType::Promotion) {
        to->removePiece();
        if (ourMove.getPromotedTo() == 'Q' || ourMove.getPromotedTo() == 'q') {
            to->setPiece(new Queen(current));
        }
        else if (ourMove.getPromotedTo() == 'R' || ourMove.getPromotedTo() == 'r') {
            to->setPiece(new Rook(current));
        }
        else if (ourMove.getPromotedTo() == 'B' || ourMove.getPromotedTo() == 'b') {
            to->setPiece(new Bishop(current));
        }
        else if (ourMove.getPromotedTo() == 'N' || ourMove.getPromotedTo() == 'n') {
            to->setPiece(new Knight(current));
        }
        to->getPiece()->setHasMoved(true);
    }

    if (current == Colour::Black){
        //loop through whitePieces, find all pawns that are en passantable, set to false
        for (vector<Piece*>::iterator it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            if ((*it)->getPieceType() == PieceType::pawn) {
                (*it)->setEnPassantable(false);
            }
        }
    }
    else{
        //loop through blackPieces, find all pawns that are en passantable, set to false
        for (vector<Piece*>::iterator it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            if ((*it)->getPieceType() == PieceType::pawn) {
                (*it)->setEnPassantable(false);
            }
        }
    }

    if (!test) {
        notifyObservers();
    }

    return true;
}

// void Board::undoMove() {
//     if (moveStack.empty()) {
//         return;
//     }

//     Move lastMove = moveStack.back();
//     Square* from = lastMove.getFrom();
//     Square* to = lastMove.getTo();

//     Piece* piece = to->getPiece();
//     from->setPiece(piece);

//     // Handle capture
//     if (lastMove.getCapturedPiece() != nullptr) {
//         to->setPiece(lastMove.getCapturedPiece());
//     } else {
//         to->setPiece(nullptr);
//     }

//     // Handle castling
//     if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
//         if (to->getX() == from->getX() + 2) {
//             // Kingside castling
//             Square* rookFrom = getSquare(5, from->getY());
//             Square* rookTo = getSquare(7, from->getY());
//             Piece* rook = rookTo->getPiece();
//             rookTo->setPiece(nullptr);
//             rookFrom->setPiece(rook);
//         } else if (to->getX() == from->getX() - 2) {
//             // Queenside castling
//             Square* rookFrom = getSquare(3, from->getY());
//             Square* rookTo = getSquare(0, from->getY());
//             Piece* rook = rookTo->getPiece();
//             rookTo->setPiece(nullptr);
//             rookFrom->setPiece(rook);
//         }
//     }

//     // Handle en passant
//     if (piece->getPieceType() == PieceType::pawn &&
//         from->getX() != to->getX() && to->getPiece() == nullptr) {
//         Square* target = getSquare(to->getX(), from->getY());
//         target->setPiece(new Pawn(piece->getColour()));
//     }

//     // Reset piece's moved state
//     if (piece->getPieceType() == PieceType::king ||
//         piece->getPieceType() == PieceType::rook) {
//         piece->setHasMoved(false);
//     }

//     // Handle promotion
//     if (piece->getPieceType() == PieceType::pawn && (to->getY() == 0 || to->getY() == 7)) {
//         delete piece;
//         to->setPiece(new Pawn(piece->getColour()));
//     }

//     moveStack.pop_back();
//     notifyObservers();
// }

// copy constructor
Board::Board(const Board& other) {
    for (const auto& row : other.board) {
        std::vector<Square*> newRow;
        for (const auto& square : row) {
            Square* newSquare = new Square(square->getX(), square->getY());
            newSquare->setBoard(this);
            if (square->getPiece() != nullptr) {
                Piece* piece = square->getPiece();
                Piece* newPiece = nullptr;
                switch (piece->getPieceType()) {
                    case PieceType::pawn:
                        newPiece = new Pawn(piece->getColour());
                        break;
                    case PieceType::rook:
                        newPiece = new Rook(piece->getColour());
                        break;
                    case PieceType::knight:
                        newPiece = new Knight(piece->getColour());
                        break;
                    case PieceType::bishop:
                        newPiece = new Bishop(piece->getColour());
                        break;
                    case PieceType::queen:
                        newPiece = new Queen(piece->getColour());
                        break;
                    case PieceType::king:
                        newPiece = new King(piece->getColour());
                        break;
                    default:
                        break;
                }
                newPiece->setHasMoved(piece->getHasMoved());
                newPiece->setEnPassantable(piece->getEnPassantable());
                newSquare->setPiece(newPiece);
                if (newPiece->getColour() == Colour::White) {
                    whitePieces.push_back(newPiece);
                } else {
                    blackPieces.push_back(newPiece);
                }
            }
            newRow.push_back(newSquare);
        }
        board.push_back(newRow);
    }
}

// assignment operator
Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }

    for (auto& row : board) {
        for (auto& square : row) {
            delete square;
        }
    }
    board.clear();

    for (const auto& row : other.board) {
        std::vector<Square*> newRow;
        for (const auto& square : row) {
            Square* newSquare = new Square(square->getX(), square->getY());
            if (square->getPiece() != nullptr) {
                Piece* piece = square->getPiece();
                Piece* newPiece = nullptr;
                switch (piece->getPieceType()) {
                    case PieceType::pawn:
                        newPiece = new Pawn(piece->getColour());
                        break;
                    case PieceType::rook:
                        newPiece = new Rook(piece->getColour());
                        break;
                    case PieceType::knight:
                        newPiece = new Knight(piece->getColour());
                        break;
                    case PieceType::bishop:
                        newPiece = new Bishop(piece->getColour());
                        break;
                    case PieceType::queen:
                        newPiece = new Queen(piece->getColour());
                        break;
                    case PieceType::king:
                        newPiece = new King(piece->getColour());
                        break;
                    default:
                        break;
                }
                newPiece->setHasMoved(piece->getHasMoved());
                newSquare->setPiece(newPiece);
            }
            newRow.push_back(newSquare);
        }
        board.push_back(newRow);
    }

    return *this;
}

bool Board::isInCheck(Colour colour) const {
    Square* kingSquare = findKing(colour);
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() != colour) {
                // std::cout << "Piece at square " << square->getX() << " " << square->getY() << " is " << piece->getSymbol() << std::endl;
                std::vector <Move> validMoves = piece->getAllMoves();

                if (piece->getPieceType() == PieceType::pawn || piece->getPieceType() == PieceType::knight) {
                    // std::cout << "validMoves.size(): " << validMoves.size() << std::endl;
                }
                // std::cout << "validMoves.size(): " << validMoves.size() << std::endl; // ZERO ??????
                for (const auto& move : validMoves) {
                    if (move.getTo() == kingSquare) {
                        return true;
                    }
                }
                // std::cout << "nvm" << std::endl;
            }
        }
    }
    // std::cout << "return reached" << std::endl;
    return false;
}

bool Board::isCheckmate(Colour colour) const {

    if (!isInCheck(colour)) {
        return false;
    }


    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            // std::cout << "Piece: " << piece << std::endl;
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getAllMoves();
                for (const auto& move : validMoves) {
                    Board copy = *this;
                    copy.movePiece(move);
                    if (!copy.isInCheck(colour)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(Colour colour) const {
    if (isInCheck(colour)) {
        return false;
    }

    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> validMoves = piece->getAllMoves();
                for (const auto& move : validMoves) {
                    
                    // Board copy = getState();
                    // copy.movePiece(move);
                    // if (!copy.isInCheck(colour)) {
                    //     return false;
                    // }

                    Board copy = *this;
                    copy.movePiece(move);
                    if (!copy.isInCheck(colour)) {
                        return false;
                    }

                }
            }
        }
    }
    return true;
}
