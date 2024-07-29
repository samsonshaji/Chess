#include "piece.h"
#include "square.h"
#include "board.h"
#include <vector>

using namespace std;

Piece::~Piece() {
    square = nullptr;
    board = nullptr;
}

PieceType Piece::getPieceType() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

Piece::Piece(Colour c) : colour(c) {}

void Piece::setSquare(Square *s) {
    square = s;
}

void Piece::setBoard(Board *b) {
    board = b;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool m) {
    hasMoved = m;
}

char Piece::getSymbol() const {
    return symbol;
}

// void Piece::addMovesInDirection(vector<Move>& moves, int xDir, int yDir) const {
//     int x = square->getX() + xDir;
//     int y = square->getY() + yDir;
    
//     while (x >= 0 && x < 8 && y >= 0 && y < 8) {
        
//         Square* targetSquare = board->getSquare(x, y);
        
//         if (targetSquare->getPiece() == nullptr) {
//             moves.push_back(Move(square, targetSquare, MoveType::Normal));
//         } 
//         else if (targetSquare->getPiece()->getColour() != colour) {
//             if (targetSquare->getPiece()->getPieceType() == PieceType::king) {
//                 board->isInCheck(targetSquare->getPiece()->getColour());
//             }
//             moves.push_back(Move(square, targetSquare, MoveType::Capture));
//             break;
//         } else {
//             break;
//         }
//         x += xDir;
//         y += yDir;
//     }
// }

void Piece::addMovesInDirection(std::vector<Move>& moves, int xDir, int yDir) const {
    int curX = square->getX();
    int curY = square->getY();
    int posX = curX + xDir;
    int posY = curY + yDir;

    // std::cout << "current: " << curX << " " << curY << std::endl;
    // std::cout << "pos: " << posX << " " << posY << std::endl;

    // PROBLEM -- board has not been defined
    // if (board) {
    //     std::cout << "board defined" << std::endl;
    // }
    // else {
    //     std::cout << "board not defined" << std::endl;
    // }

    // if (board->getSquare(posX, posY) == nullptr) {
    //     std::cout << "null" << std::endl;
    // }
    // else if (board->getSquare(posX, posY)->getPiece() == nullptr) {
    //     std::cout << "empty" << std::endl;
    // }
    // else {
    //     std::cout << "not empty" << std::endl;
    // }

    while(posX >= 0 && posX < 8 && posY >= 0 && posY < 8){
        if (board->getSquare(posX, posY) && board->getSquare(posX, posY)->getPiece() != nullptr) {
            if (board->getSquare(posX, posY)->getPiece()->getColour() != colour) {
                moves.push_back(Move(square, board->getSquare(posX, posY), MoveType::Capture));
            }
            break;
        }
        moves.push_back(Move(square, board->getSquare(posX, posY), MoveType::Normal));
        posX+=xDir;
        posY+=yDir;
    }
}
