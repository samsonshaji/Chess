#include "graphicsobserver.h"
#include "board.h"
#include <string>
#include <sstream>

GraphicsObserver::GraphicsObserver(Subject &sub) : subject(sub), w(500, 500) {
    subject.attach(this);
}

GraphicsObserver::~GraphicsObserver() {
    subject.detach(this);
}

// void GraphicsObserver::notify() {
//     std::vector<std::vector<Square*>> board = subject.getState();

//     for (int x = 0; x < 8; ++x) {
//         for (int y = 0; y < 8; ++y) {
//             Square* square = board[x][y];
//             if (square->getPiece()) {
//                 char pieceSymbol = square->getPiece()->getSymbol();
//                 std::string pieceSymbolStr(1, pieceSymbol);
//                 xw.drawString(x * 60, y * 60, pieceSymbolStr);
//             } else {
//                 xw.drawString(x * 60, y * 60, "_");
//             }
//         }
//     }
// }

void GraphicsObserver::notify() {
if(!gridDrawn){
    w.fillRectangle(0, 0, 500, 500, Xwindow::Brown);

    for(int i = 0; i < 2; i++){
        w.drawBigString(50*1 + 25, 25 + (450 * i), "A", Xwindow::White);
        w.drawBigString(50*2 + 25, 25 + (450 * i), "B", Xwindow::White);
        w.drawBigString(50*3 + 25, 25 + (450 * i), "C", Xwindow::White);
        w.drawBigString(50*4 + 25, 25 + (450 * i), "D", Xwindow::White);
        w.drawBigString(50*5 + 25, 25 + (450 * i), "E", Xwindow::White);
        w.drawBigString(50*6 + 25, 25 + (450 * i), "F", Xwindow::White);
        w.drawBigString(50*7 + 25, 25 + (450 * i), "G", Xwindow::White);
        w.drawBigString(50*8 + 25, 25 + (450 * i), "H", Xwindow::White);

        w.drawBigString(25 + (450 * i), 50*9 - 25, "1", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*8 - 25, "2", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*7 - 25, "3", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*6 - 25, "4", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*5 - 25, "5", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*4 - 25, "6", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*3 - 25, "7", Xwindow::White);
        w.drawBigString(25 + (450 * i), 50*2 - 25, "8", Xwindow::White); 
    }
    gridDrawn = true;
    }   

    for (int i=7; i>=0; i--) {
    for (int j=0; j<8; j++) {
        if((i+j)%2 == 0){
            w.fillRectangle(50*(j + 1), 50*(8-i), 50, 50, Xwindow::Black);
        } else {
            w.fillRectangle(50*(j + 1), 50*(8-i), 50, 50, Xwindow::White);
        }

        std::vector<std::vector<Square*>> board = subject.getState();

        char piece;
        if(board[i][j]->getPiece() == nullptr){
            piece = '_';
        } else {
            piece = board[i][j]->getPiece()->getSymbol();
        }
        
        if(piece != ' ' && piece != '_'){ 
            std::stringstream ss;
            std::string s;
            ss << piece;
            ss >> s;
        
            if(piece + 0 > 96){
                w.drawBigString(50*(j + 1) + 25, 50*(9-i) - 25, s, Xwindow::Blue);
            } else {
                w.drawBigString(50*(j + 1) + 25, 50*(9-i) - 25, s, Xwindow::Red);
            }  
        }
    }
    }
}

